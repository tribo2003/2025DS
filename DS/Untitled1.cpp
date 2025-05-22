



































































































/*
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;  
    TreeNode* right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};


TreeNode* buildTree(const vector<int>& node) {
    if((node.empty())||(node[0]==-1)){   
        return nullptr;
    } 
    vector<TreeNode*> tree(node.size(),nullptr);
    
    for(int i=0; i<node.size(); i++){
        if(node[i]==(-1)){      
            continue;
        }

        if(tree[i]==nullptr){
            tree[i]=new TreeNode(node[i]);
        }

        int l=2*i+1;
        int r=2*i+2;

        if((l<node.size())&&node[l]!=-1){
            tree[l]=new TreeNode(node[l]);
            tree[i]->left=tree[l];
        }

        if((r<node.size())&&(node[r]!=-1)){
            tree[r]=new TreeNode(node[r]);
            tree[i]->right=tree[r];
        }
    }
    
    return tree[0];
}


void inorder(TreeNode* root){
    if(root!=nullptr){
        inorder(root->left);
        cout<<(root->data)<<" ";
        inorder(root->right);    
    }
}

void preorder(TreeNode* root){
    if(root!=nullptr){
        cout<<(root->data)<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root){
    if(root!=nullptr){
        postorder(root->left);
        postorder(root->right);
        cout<<(root->data)<<" ";
    }
}

bool search(TreeNode* root, int target, vector<int>& cumul) {
    
    if (root==nullptr){  
        return false;
    }

    cumul.push_back(root->data);
    
    if((root->data)==target){
        return true;
    }
    if((search(root->left,target,cumul))||(search(root->right,target,cumul))){
        return true;
    }

    cumul.pop_back();
    return false;
}

int main() {
    int n,target;
    cin>>n;
    
    vector<int>location(n);
    for (int i=0; i<n; i++) {
        cin>>location[i];
    }

    cin>>target;
    
    TreeNode* root=buildTree(location);
    
    inorder(root);
    cout<<endl;

    preorder(root);
    cout<<endl;

    postorder(root);
    cout<<endl;
    
    

    vector<int> cumul;
    if(search(root,target,cumul)==true){
        int sum=0;
        for(int i=0;i<cumul.size();i++){
            sum+=cumul[i];
        }
        cout<<sum;
    }else{
        cout<<(-1);
    }
    
    return 0;
}
*/

/*
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;


typedef long long ll;
vector<ll> zone;

ll update(int index, ll value){
    ll ori=zone[index];
    zone[index]=value;

    return ori;
}

ll query(int start, int end){
    if((start>0)&&(end<zone.size())&&(start<=end)){
        ll sum=0;
        for(int j=start; j<=end; j++){
            sum+=zone[j];
        }
        return sum;   
    }
}



int main(){
    int n, x;
    cin>>n;
    zone.resize(n);
    for(int i=0; i<n; i++){
        cin>>zone[i];
    }

    string op;
    cin>>x;
    for(int i=0; i<x; i++){
        cin>>op;
        if(op=="u"){
            int ind;
            ll val;
            cin>>ind>>val;
            cout<<update(ind,val)<<endl;
        }else if(op=="q"){
            int start,end;
            cin>>start>>end;
            cout<<query(start,end)<<endl;
        }
    }

    return 0;

}
*/


/*
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;


typedef long long ll;
struct Node{
    ll sum;
    ll maxval;
};

vector<ll> zone;
vector<Node>segT;

void build(int node, int l, int r){
    if(l==r){
        segT[node].sum=zone[l];
        segT[node].maxval=zone[l];
        return;
    }
    int mid=(l+r)/2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    segT[node].sum=segT[2*node].sum+segT[2*node+1].sum;
    segT[node].maxval=max(segT[2*node].maxval, segT[2*node+1].maxval);
}



void update(int node, int l, int r, int index, ll value){
    if(l==r){
        segT[node].sum=value;
        segT[node].maxval=value;
        return;
    }
    int mid=(l+r)/2;
    if(index<=mid){
        update(2*node, l, mid, index, value);
    }else{
        update(2*node+1, mid+1, r, index, value);
    }
    segT[node].sum=segT[2*node].sum+segT[2*node+1].sum;
    segT[node].maxval=max(segT[2*node].maxval,segT[2*node+1].maxval);
}

Node query(int node, int l, int r, int ql, int qr){
    if((ql>r)||(qr<l)){
        return{0,0};
    }
    if((ql<=l)&&(r<=qr)){
        return segT[node];
    }
    int mid=(l+r)/2;
    Node left=query(2*node, l, mid, ql, qr);
    Node right=query(2*node+1, mid+1, r, ql, qr);
    
    return{left.sum+right.sum, max(left.maxval, right.maxval)};
}



int main(){
    int n, x;
    cin>>n;
    zone.resize(n);
    segT.resize(4*n);
    for(int i=0; i<n; i++){
        cin>>zone[i];
    }
    build(1, 0, n-1);

    string op;
    cin>>x;
    for(int i=0; i<x; i++){
        cin>>op;
        if(op=="u"){
            int ind;
            ll val;
            cin>>ind>>val;
            cout<<zone[ind]<<endl;
            zone[ind]=val;
            update(1, 0, n-1, ind, val);
        }else if(op=="q"){
            int l,r;
            cin>>l>>r;
            Node res=query(1, 0, n-1, l, r);
            cout<<res.sum<<" "<<res.maxval<<endl;
        }
    }

    return 0;

}
*/


/*
#include<iostream>
#include<stdlib.h>
#include<vector>


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
*/

/*
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
*/



