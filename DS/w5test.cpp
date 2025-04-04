#include "ds_q5.hpp"
#include <vector>
#include<iostream>

using namespace std;

vector<vector<int>> mapDamage(DamageNode_t *head, int m, int n) {
	// Implement this function for assignment 5-1



    /*
            perp {1,next} {1,next}<{2,next}<{6,next}<{8,next}
             |        v        v                         ^
        (m-1)|   {5,next} {3,next}>{0,next}>{0,next} {1,next}
             |        v                                  ^
             v   {5,next}>{2,next}>{4,next}>{9,next}>{7,next}
                   hori  ----------------------------------->
                                   (n-1)
    
    
    */
    vector<vector<int>> matrix(m,vector<int>(n));
    DamageNode_t *current=head;
    int perp=0;
    int r=m-1;
    int hori=0;
    int c=n-1;

    while((perp<=r)&&(hori<=c)){
        for(int i=perp; i<=r; i++){
            if(current){
                matrix[i][hori]=current->damage;
                current=current->next;
            }
        }
        hori++;

        for(int i=hori;i<=c;i++){
            if(current){
                matrix[perp][i]=current->damage;
                current=current->next;
            }
        }
        r--;

        if(hori<=c){
            for(int i=r;i>=perp;i--){
                if(current){
                    matrix[i][c]=current->damage;
                    current=current->next;
                }
            }
            c--;
        }

        if(perp<=r){
            for(int i=c;i>=hori;i--){
                if(current){
                    matrix[perp][i]=current->damage;
                    current=current->next;
                }
            }
            perp++;
        }
    }
    return matrix;
}

vector<vector<int>> mapRotatingDamage(DamageNode_t *head, int m, int n, int k) {
	// Implement this function for assignment 5-2
    vector<vector<int>> matrix(m, vector<int>(n, 0));
    if (!head || m == 0 || n == 0) return matrix;

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;
    int count = 0;  // 当前已填充的连续攻击次数
    
    DamageNode_t* current = head;
    DamageNode_t* prev = nullptr;
    DamageNode_t* rotation_start = head;  // 旋转起始点

    while (top <= bottom && left <= right && current) {
        // 逆时针填充左列（从上到下）
        for (int i = top; i <= bottom && current; i++) {
            matrix[i][left] = current->damage;
            prev = current;
            current = current->next;
            if (++count == k && current) {
                // 执行旋转
                DamageNode_t* new_head = current;
                prev->next = nullptr;
                
                // 找到当前链表的尾节点
                DamageNode_t* tail = current;
                while (tail->next) tail = tail->next;
                
                // 将原头部接到尾部
                tail->next = rotation_start;
                rotation_start = current = new_head;
                count = 0;
            }
        }
        left++;
        if (top > bottom || left > right) break;

        // 填充底行（从左到右）
        for (int i = left; i <= right && current; i++) {
            matrix[bottom][i] = current->damage;
            prev = current;
            current = current->next;
            if (++count == k && current) {
                DamageNode_t* new_head = current;
                prev->next = nullptr;
                
                DamageNode_t* tail = current;
                while (tail->next) tail = tail->next;
                
                tail->next = rotation_start;
                rotation_start = current = new_head;
                count = 0;
            }
        }
        bottom--;
        if (top > bottom || left > right) break;

        // 填充右列（从下到上）
        for (int i = bottom; i >= top && current; i--) {
            matrix[i][right] = current->damage;
            prev = current;
            current = current->next;
            if (++count == k && current) {
                DamageNode_t* new_head = current;
                prev->next = nullptr;
                
                DamageNode_t* tail = current;
                while (tail->next) tail = tail->next;
                
                tail->next = rotation_start;
                rotation_start = current = new_head;
                count = 0;
            }
        }
        right--;
        if (top > bottom || left > right) break;

        // 填充顶行（从右到左）
        for (int i = right; i >= left && current; i--) {
            matrix[top][i] = current->damage;
            prev = current;
            current = current->next;
            if (++count == k && current) {
                DamageNode_t* new_head = current;
                prev->next = nullptr;
                
                DamageNode_t* tail = current;
                while (tail->next) tail = tail->next;
                
                tail->next = rotation_start;
                rotation_start = current = new_head;
                count = 0;
            }
        }
        top++;
    }
    return matrix;
	return {};
}

#ifndef OJ_MODE
// This main function is for local testing only.
// It will NOT be compiled or executed on the OJ system.
int main() {
    // TODO: Write test code here to verify your implementation.
    int m,n,L,k;
    cin>>m>>n>>L;
    
    DamageNode_t* head=nullptr;
    DamageNode_t* tail=nullptr;
    
    for(int i=0; i<L; i++){
        int damage;
        cin>>damage;
        DamageNode_t* newNode=new DamageNode_t{damage,nullptr};
        if(!head){
            head=newNode;
            tail=newNode;
        }else{
            tail->next=newNode;
            tail=newNode;
        }
    }
    cin>>k;
    
    vector<vector<int>>result=mapRotatingDamage(head,m,n,k);
    cout<<"output: "<<endl;
    for(const auto& row:result){
        for(int val:row){
            cout<<val<<" ";
        }
        cout<<endl;
    }
    
    while(head){
        DamageNode_t* temp=head;
        head=head->next;
        delete temp;
    }
    return 0;
}
#endif
