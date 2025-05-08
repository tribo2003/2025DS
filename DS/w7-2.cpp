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
        segT[node].maxval=zone[r];
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
        segT[node].maxval;
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
    if((ql>r)||(qr<1)){
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