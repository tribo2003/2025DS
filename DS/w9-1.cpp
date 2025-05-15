#include<iostream>

using namespace std;
#define MAX_VERTICES 200
struct Node{
    int vertex;
    int cost;
    Node* next;
    Node(int x):vertex(x), next(nullptr){}
};

void addEdge(int u, int v, int c){
    Node* newnode=new Node(v);
    newnode->cost=c;
    newnode->next=;
}






int main(){
    int n, m;
    cin>>n>>m;
    
    return 0;
}