#include<stdlib.h>
#include<iostream>
#include<vector>
#include<climits>

using namespace std;

typedef long long ll;

struct Node{
    int vertex;
    int weight;
    Node* next;
    Node(int x):vertex(x), weight(0), next(nullptr){}
};

vector<Node*> adj;
vector<ll> key;
vector<int> parent;
vector<int> visited;

void addEdge(int u, int v, int c){
    Node* newnode1=new Node(v);
    newnode1->weight=c;
    newnode1->next=adj[u];
    adj[u]=newnode1;

    Node* newnode2=new Node(u);
    newnode2->weight=c;
    newnode2->next=adj[v];
    adj[v]=newnode2;
}

void prim(int n){
    for(int i=0; i<n; i++){
        key[i]=INT_MAX;
        parent[i]=-1;
        visited[i]=0;
    }
    key[0]=0;

    for(int count=0; count<(n-1); count++){
        int x=-1;
        int min=INT_MAX;
        for(int i=0; i<n; i++){
            if((!visited[i])&&(key[i]<min)){
                min=key[i];
                x=i;
            }
        }

        visited[x]=1;
        Node* temp=adj[x];
        while(temp!=nullptr){
            int a=temp->vertex;
            int b=temp->weight;
            if((!visited[a])&&(b<key[a])){
                key[a]=b;
                parent[a]=x;
            }
            temp=temp->next;
        }
    }

     
}





int main(){
    int n, m;
    cin>>n>>m;

    adj.resize(n);
    key.resize(n);
    parent.resize(n);
    visited.resize(n);

    for(int i=0; i<m; i++){
        int u, v, c;
        cin>>u>>v>>c;
        addEdge(u-1,v-1,c);
    }

    prim(n);

    ll sum=0;
    for(int i=1; i<key.size(); i++){
        sum+=key[i];
    }
    cout<<sum;
   
    return 0;
}