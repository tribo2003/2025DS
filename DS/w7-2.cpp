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



ll update(int index, ll value){
    ll ori=zone[index];
    zone[index]=value;

    return ori;
}

void query(int start, int end){
    if((start>0)&&(end<zone.size())&&(start<=end)){
        
        for(int j=start; j<=end; j++){
            sum+=zone[j];
            if(maxval<=zone[j]){
                maxval=zone[j];
            }
        }

        return;   
    }
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
            cout<<update(ind,val)<<endl;
        }else if(op=="q"){
            int start,end;
            cin>>start>>end;
            query(start,end);
            cout<<sum<<" "<<maxval<<endl;
        }
    }

    return 0;

}