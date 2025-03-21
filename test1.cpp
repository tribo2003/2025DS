#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

long long mintotal(vector<long long>& elevation){
    int n = elevation.size();

    long long maxElevation=*max_element(elevation.begin(),elevation.end());
    long long minimum=LLONG_MAX; // 使用 long long 避免溢出

    for(int i=0; i<n; ++i){
        vector<long long> altitude(n);

        // 將 elevation[i] 設為爬升點
        altitude[i]=elevation[i];
        long long current=altitude[i];

        // 從爬升點往前計算 altitude
        for(int j=i-1; j>=0; --j){
            current=max(current,elevation[j]);
            altitude[j]=min(current,maxElevation);
            current=altitude[j];
        }

        // 從爬升點往後計算 altitude
        current=altitude[i];
        for(int j=i+1; j<n; ++j){
            current=max(current,elevation[j]);
            altitude[j]=min(current,maxElevation);
            current=altitude[j];
        }

        // 計算總和
        long long sum=0;
        for(int j=0; j<n; ++j){
            sum=sum+altitude[j];
        }

        // 更新最小值
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