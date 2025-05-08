#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

/*
Q: 找 ＃of 朋友群
單向linklist
新匯入關係先找朋友在不在linklist裡：
-在 加入現在的linklist
-不在 加入新的linklist
*使用vector儲存linklist:指向各條linklist
最後算vectort長度
*/

struct Node{
    int data;
    Node* next;
    Node(int val): data(val), next(nullptr){}
};

vector<Node>num_relation;

void push_back(int x){
    Node* newback=new Node(x);                    //(newback) -> {element,NULL}             

    if(head==nullptr){                 //空陣列   
        head=newback;                                           //(head) -> {element,NULL}        
    }else{                             //非空陣列=>只在乎原本指向的最後一個Node{data,nullptr}
        Node* current=head;                                     //current指向head指向的node 
        while(current->next!=nullptr){                          //(current) -> {data,next}
            current=current->next;                              //(current) -> {原next指向的data,原next指向的next}
        }
        current->next=newback;                                  //(current)-> {element,NULL}

    }
}
void search(int x){

}


int main(){
    int n, m;
    cin>>n>>m;

    for(int i=0; i<m; i++){
        int rs, rf;
        cin>>rs>>rf;
        if(num_relation.size()==0){        //初始： num_relation[0]與其連接的linklist  
            Node* head=new Node(rs);
            num_relation[0]=*head;
        }
        for(int j=0; j<num_relation.size(); j++){
            if(search(rs)==true){

            };
        }
        
    }


    return 0;
}