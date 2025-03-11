#include <iostream>
#include <stdlib.h>

using namespace std;


int maxleaves(int rnum_leaves, int cnum_leaves, int **leaves, bool *malefrog){
    int maxl=0;
    *malefrog=false;

    // 橫向
    // 正向找公蛙
    for(int r=0; r<rnum_leaves; r++){
        for(int pc=0; pc<cnum_leaves; pc++){
            if(leaves[r][pc]==1) {  // 找到公蛙，開始計數
                *malefrog=true;

                int p_count=0;
                for(int j=pc+1; j<cnum_leaves; j++){  // 找母蛙
                    if(leaves[r][j]==0){
                        p_count++;
                    }else if(leaves[r][j]==2){  // 找到母蛙
                        maxl=max(maxl, p_count);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    // 反向找公蛙
    for(int r=0; r<rnum_leaves; r++){
        for(int nc=cnum_leaves-1; nc>=0; nc--){
            if(leaves[r][nc]==1){  // 找到公蛙，開始計數

                int n_count=0;
                for(int j=nc-1; j>=0; j--){  // 找母蛙
                    if(leaves[r][j]==0){
                        n_count++;
                    }else if(leaves[r][j]==2){  // 找到母蛙
                        maxl=max(maxl, n_count);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
    }

    //縱向
    // 正向找公蛙
    for(int c=0; c<cnum_leaves; c++){
        for(int pr=0; pr<rnum_leaves; pr++){
            if(leaves[pr][c]==1) {  // 找到公蛙，開始計數
                *malefrog=true;

                int p_count=0;
                for(int j=pr+1; j<rnum_leaves; j++){  // 找母蛙
                    if(leaves[j][c]==0){
                        p_count++;
                    }else if(leaves[j][c]==2){  // 找到母蛙
                        maxl=max(maxl, p_count);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    // 反向找公蛙
    for(int c=0; c<cnum_leaves; c++){
        for(int nr=rnum_leaves-1; nr>=0; nr--){
            if(leaves[nr][c]==1){  // 找到公蛙，開始計數

                int n_count=0;
                for(int j=nr-1; j>=0; j--){  // 找母蛙
                    if(leaves[j][c]==0){
                        n_count++;
                    }else if(leaves[j][c]==2){  // 找到母蛙
                        maxl=max(maxl, n_count);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    return maxl;
}


int main(){
    // 初始化
    int rnum_leaves, cnum_leaves;
    cin>>rnum_leaves>>cnum_leaves;
    
    int **leaves=new int *[rnum_leaves];
    for(int i=0; i<rnum_leaves; i++) {
        leaves[i]=new int[cnum_leaves];
    }

    for(int i=0; i<rnum_leaves; i++){
        for(int j=0; j<cnum_leaves;j++){
            cin>>leaves[i][j];
        }
    }

    // 呼叫函數
    bool malefrog;
    int max_leaves=maxleaves(rnum_leaves, cnum_leaves, leaves, &malefrog);
    
    if((max_leaves==0)||(!malefrog)){
        cout<<"0";
    }else{
        cout<<max_leaves;
    }
    
    // 釋放動態分配的記憶體
    for(int i=0; i<rnum_leaves; i++){
        delete[] leaves[i];
    }
    delete[] leaves;

    return 0;
}