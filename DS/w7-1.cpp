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