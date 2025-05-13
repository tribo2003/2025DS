#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<set>



using namespace std;

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


void free(Node* current){
    while(current!=nullptr){
        Node* temp=current;
        current=current->next;
        delete temp;
    }
}


int num_part(int n, const vector<pair<int, int>>& relations, int exclude){
    vector<Node*>num_relation;

    for(const auto& relation: relations){
        int r1=relation.first;
        int r2=relation.second;

        if((r1==exclude)||(r2==exclude)){
            continue;
        }
        
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

    set<int> connected;
    for(Node* relation: num_relation){
        Node* current=relation;
        while(current!=nullptr){
            connected.insert(current->data);
            current=current->next;
        }
    }

    for(int i=1; i<=n; i++){
        if(i==exclude){
            continue;
        }
        if(connected.find(i)==connected.end()){
            Node* isolated=new Node(i);
            num_relation.push_back(isolated);
        }
    }

    for(Node* relation: num_relation){
        free(relation);
    }


    return num_relation.size();
}

/*
把描述關聯m行指令中的每個點各自單獨刪掉 算出個別導出的總part數
因為全部留著的(原始的)總part數一定是最少的 所以最終導出所有比全留著還多part數的點
<idea> 
1. 用迴圈 在單獨算完刪除某點後的總part數 直接跟原始的比 如果比較大就直接輸出當下刪的那個點 x
2. 開vector存 刪掉的點及其對應的總part數 最後再檢查該vector所有比原始總part數大的值 輸出其對應刪除的點
*/

int main(){
    int n, m;
    cin>>n>>m;
    vector<pair<int, int>> relations;

    for(int i=0; i<m; i++){
        int r1, r2;
        cin>>r1>>r2;
        
        relations.emplace_back(r1,r2);
    }

    int part_original=num_part(n,relations,-1);

    vector<int> arti_pts;
    for(int i=1; i<=n; i++){
        int part_exclude=num_part(n,relations,i);
        if(part_exclude>part_original){
            arti_pts.push_back(i);
        }
    }

    if(arti_pts.empty()){
        cout<<"none"<<endl;
    }else{
        for(int x:arti_pts){
            cout<<x<<" ";
        }
        cout<<endl;
    }

    return 0;
}