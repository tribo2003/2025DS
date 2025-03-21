#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;


/*
<i是爬升點(直接記錄到altitude[i]) 每個i都試過 將sum存到比大小陣列 輪完每個i後找min>

找max
altitude每輪結束後要裡面的值要清空

爬升點
-前=>遞減或維持
-後=>遞增或維持

*/
long long mintotal(vector<long long>& elevation){

    long long maxElevation=*max_element(elevation.begin(),elevation.end());
    long long minimum=LLONG_MAX;

    for(int i=0; i<elevation.size(); ++i){
        vector<long long> altitude(elevation.size());

        altitude[i]=elevation[i];
        long long current=altitude[i];

        //爬升點i前
        for(int j=i-1; j>=0; --j){
            current=max(current,elevation[j]);
            altitude[j]=min(current,maxElevation);
            current=altitude[j];
        }

        //爬升點i時
        current=altitude[i];

        //爬升點i後
        for(int j=i+1; j<elevation.size(); ++j){
            current=max(current,elevation[j]);
            altitude[j]=min(current,maxElevation);
            current=altitude[j];
        }


        long long sum=0;
        for(int j=0; j<elevation.size(); ++j){
            sum=sum+altitude[j];
        }


        if(sum<minimum){
            minimum=sum;
        }

    
    }

    return(long long)minimum;
}


int main() {
    int n;
    cin>>n;

    vector<long long> elevation(n);
    for(int i=0; i<n; i++){
        cin>>elevation[i];
    }

    cout<<mintotal(elevation)<<endl;
    return 0;
}