#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;


typedef long long ll;
vector<ll> zone;
ll sum=0;
ll maxval=0;

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
            query(start,end);
            cout<<sum<<" "<<maxval<<endl;
        }
    }

    return 0;

}