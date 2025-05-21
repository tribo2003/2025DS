#include<iostream>
#include<stdlib.h>
#include<vector>


using namespace std;

/*
Q: 找 ＃of 朋友群
單向linklist
新匯入關係先找朋友在不在linklist裡：
-在 加入現在的linklist
-不在 加入新的linklist(兩人在不同linklist裡->合併linklist)
*使用vector儲存linklist:指向各條linklist
最後算vector長度
*/

struct Node{
    int data;
    Node* next;
    Node(int val): data(val), next(nullptr){}
};

vector<Node*>num_relation;

bool search(Node* head, int x){
    Node* current=head;
    while(current!=nullptr){
        if(current->data==x){
            return true;
        }
        current=current->next;
    }
    return false;
}

void append(Node*& head, int x){
    Node* newNode=new Node(x);
    if(head==nullptr){
        head=newNode;
    }else{
        Node* current=head;
        while(current->next!=nullptr){
            current=current->next;
        }
        current->next=newNode;
    }
}

void merge(Node*& l1, Node*& l2){
    if(l1==nullptr){
        l1=l2;
        return;
    }
    Node* current=l1;
    while(current->next!=nullptr){
        current=current->next;
    }
    current->next=l2;
}

void free(){
    for(Node* relation:num_relation){
        Node* current=relation;
        while(current!=nullptr){
            Node* temp=current;
            current=current->next;
            delete temp;
        }
    }
}

void relations(int r1, int r2){
    int aidx=-1, bidx=-1;
        for(int j=0; j<num_relation.size(); j++){
            if(search(num_relation[j], r1)){
                aidx=j;
            }
            if(search(num_relation[j], r2)){
                bidx=j;
            }
        }
        if((aidx==-1)&&(bidx==-1)){
            Node* newRelation=new Node(r1);
            append(newRelation, r2);
            num_relation.push_back(newRelation);
        }else if((aidx!=-1)&&(bidx==-1)){
            append(num_relation[aidx], r2);
        }else if((aidx==-1)&&(bidx!=-1)){
            append(num_relation[bidx], r1);
        }else if((aidx!=-1)&&(bidx!=-1)&&(aidx!=bidx)){
            merge(num_relation[aidx], num_relation[bidx]);
            num_relation.erase(num_relation.begin()+bidx);
        }

}



int main(){
    int n, m;
    cin>>n>>m;

    for(int i=0; i<m; i++){
        int r1, r2;
        cin>>r1>>r2;
        relations(r1,r2);  
    }

    int TotalStuInGroup=0;
    for(Node* relation:num_relation){
        Node* current=relation;
        while(current!=nullptr){
            TotalStuInGroup++;
            current=current->next;
        }
    }

    int isolated=n-TotalStuInGroup;

    cout<<num_relation.size()+isolated<<endl;

    free(); 

    return 0;
}