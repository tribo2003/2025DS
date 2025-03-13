#include<iostream>
#include<stdlib.h>

using namespace std;

#define MAX_TERMS 200  
/*size of terms array*/ 
typedef struct{ 
    float coef; 
    int expon;
}polynomial; 
polynomial terms [MAX_TERMS];
int avail=0;

void attach(float coeff, int expone){
    if(avail>=MAX_TERMS){
        cout<<"too many terms"<<endl;
        exit(1);
    }
    terms[avail].coef=coeff;
    terms[avail++].expon=expone;
}

int compare(int a, int b){
    if(a>b){
        return 1;
    }else if(a==b){
        return 0;
    }else{
        return -1;
    }
}


/*減法會碰到的情況:
同次方數

缺a: b係數變負
缺b: a係數正常

ab都有
ab不同:正常運算
a=b:抵銷但不會占用term的格子=>直接跳下一個檢查

*/
void sub_polynomial(int starta, int startb, int finisha, int finishb, int* startd, int* finishd, int* num_term){
    float coeff;
    *num_term=0;
    *startd=avail;

    //a,b都還有剩
    while((starta<=finisha)&&(startb<=finishb)){
        switch(compare(terms[starta].expon,terms[startb].expon)){
            case -1: //a<b
                attach((-terms[startb].coef),terms[starta].expon);
                (*num_term)++;
                startb++;
                break;
            case 0: //a=b
                coeff=terms[starta].coef-terms[startb].coef;
                if(coeff!=0){
                    attach(coeff,terms[starta].expon);
                    (*num_term)++;
                }
                starta++;
                startb++;
                break;
            case 1: //a>b
                attach(terms[starta].coef,terms[starta].expon);
                (*num_term)++;
                starta++;
                break;
        }
    }

    //b沒了
    for(; starta<=finisha; starta++){
        attach(terms[starta].coef,terms[starta].expon);
        (*num_term)++;
    }

    //a沒了=>輸出-(b剩餘項數)
    for(; startb<=finishb; startb++){
        attach(-terms[startb].coef,terms[startb].expon);
        (*num_term)++;
    }
    *finishd=avail-1;
}

int main(){
    int starta, startb, finisha, finishb, startd, finishd;
    int num_term=0;

    int m, n;
    cin>>m;
    starta=avail;
    for(int i=0; i<m; i++){
        cin>>terms[avail].coef>>terms[avail].expon;
        avail++;
    }
    finisha=avail-1;

    cin>>n;
    startb=avail;
    for(int i=0; i<n; i++){
        cin>>terms[avail].coef>>terms[avail].expon;
        avail++;
    }
    finishb=avail-1;

    sub_polynomial(starta, startb, finisha, finishb, &startd, &finishd, &num_term);
    

    cout<<num_term<<endl;

    for(int i=0; i<num_term; i++){
        cout<<terms[i].coef<<" "<<terms[i].expon<<endl;
    }
    
    return 0;
}