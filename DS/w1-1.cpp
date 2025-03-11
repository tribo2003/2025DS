#include <iostream>
#include <stdlib.h>

using namespace std;


int maxleaves(int num_leaves, int leaves[], bool *malefrog){
    int maxl=0;
    *malefrog=false;

    // 正向找公蛙
    for(int i=0; i<num_leaves; i++){
        if(leaves[i]==1) {  // 找到公蛙，開始計數
            *malefrog=true;

            int p_count=0;
            for(int j=i+1; j<num_leaves; j++){  // 找母蛙
                if(leaves[j]==0){
                    p_count++;
                }else if(leaves[j]==2){  // 找到母蛙
                    maxl=max(maxl, p_count);
                    break;
                }else{
                    break;
                }
            }
        }
    }

    // 反向找公蛙
    for(int i=num_leaves-1; i>=0; i--){
        if(leaves[i]==1){  // 找到公蛙，開始計數

            int n_count=0;
            for(int j=i-1; j>=0; j--){  // 找母蛙
                if(leaves[j]==0){
                    n_count++;
                }else if(leaves[j]==2){  // 找到母蛙
                    maxl=max(maxl, n_count);
                    break;
                }else{
                    break;
                }
            }
        }
    }

    return maxl;
}


int main(){
    // 初始化
    int num_leaves;
    cin>>num_leaves;
    int *leaves=new int[num_leaves];

    for(int i=0; i<num_leaves; i++) {
        cin>>leaves[i];
    }

    // 呼叫函數
    bool malefrog;
    int max_leaves=maxleaves(num_leaves, leaves, &malefrog);
    
    if((max_leaves==0)||(!malefrog)){
        cout<<"0";
    }else{
        cout<<max_leaves;
    }
    
    // 釋放動態分配的記憶體
    delete[] leaves;

    return 0;
}