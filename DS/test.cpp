#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;


/*
<i是爬升點(直接記錄到altitude[i]並pullup[i]=true) 每個i都試過 將sum存到比大小陣列 輪完每個i後找min>

找max
altitude每輪結束後要裡面的值要清空
pullup每輪結束後要將裡面的值先全改為false

如果pullup[j]=true: 
altitude[j後面的]=max(altitude[j],elevation[j後面的]) 
altitude[j前面的]=min(altitude[j],elevation[j前面的])

若altitude[j]==NULL才做 若非空的直接跳下一個j

*/
int mintotal(vector<int>& elevation){
    int n=elevation.size();
    if(n==0){
        return 0;
    }

    // 找出 elevation 中的最大值
    auto maxIt = max_element(elevation.begin(), elevation.end());
    int maxElevation = *maxIt;
    int maxIndex = distance(elevation.begin(), maxIt);


    vector<int> total;
    //i是爬升點
    for(int i=0; i<n; ++i){
        cout<<endl;
        cout<<i<<"th pullup: ";
        vector<int> altitude(n,INT_MAX); // 初始化 altitude 為無窮大

        altitude[i]=elevation[i];
        int current=altitude[i];

        // 從爬升點往前計算 altitude
        for(int j=0; j<n; ++j){
            if(i>maxIndex){
                if(j<=maxIndex){
                    current=maxElevation;
                    altitude[j]=current;
                    current=elevation[j+1];
                }else if(j==i){
                    current=altitude[j];
                }else{
                    altitude[j]=max(current,altitude[i]);
                }
                cout<<altitude[j]<<" "<<current<<endl;

            }else{
                if(j==i){
                    current=altitude[j];
                }else{
                    current=max(current,elevation[j]);
                    altitude[j]=min(current,maxElevation);
                    current=altitude[j];
     
               }
               cout<<altitude[j]<<" "<<current<<endl;
            }
            
        }      
        


        long long sum=0;
        for(int j=0; j<n; ++j){
            sum=sum+altitude[j];
        }

        total.push_back(sum);
    }

    //找最小值
    long long minimum=*min_element(total.begin(),total.end());
    return minimum;
}


int main(){
    int n;
    cin>>n;

    vector<int> elevation(n);
    for(int i=0; i<n; i++){
        cin>>elevation[i];
    }

    cout<<mintotal(elevation)<<endl;
    return 0;
}