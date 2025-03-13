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

void bubble(int start, int finish){
    for(int i=start; i<finish; i++){
        for(int j=start; j<finish-(i-start); j++){
            if(terms[j].expon<terms[j+1].expon){
                polynomial temp=terms[j];
                terms[j]=terms[j+1];
                terms[j+1]=temp;
            }
        }
    }
}



/*
pmult:相乘後同類項合併(有負數的padd)

-相乘
coef:mult
expo:add

-同類項合併
?:可能會需要重新排序

c:存相乘完
d:存同類項合併完
*/
void mult_polynomial(int starta, int startb, int finisha, int finishb, int* startc, int* finishc, int* startd, int* finishd, int* num_term){
    float coeff;
    *num_term=0;
    *startc=avail;


    //相乘
    while(starta<=finisha){
        for(int i=startb; i<=finishb; i++){
            coeff = terms[starta].coef*terms[i].coef;
            if(coeff!=0){
                attach(coeff, terms[starta].expon+terms[i].expon);
            }
        }
        starta++;
    }

    *finishc=avail-1;

    bubble(*startc, *finishc);


    //同類項合併: c內項數合併
    *startd=avail;
    int current=*startc;

    while(current<=*finishc){
        float sum_coef=terms[current].coef;
        int current_expon=terms[current].expon;

        // 合併同類項
        while(((current+1)<=*finishc)&&(terms[current+1].expon==current_expon)){
            sum_coef+=terms[current+1].coef;
            current++;
        }
        if(sum_coef != 0){
            attach(sum_coef, current_expon);
            (*num_term)++;
        }
        current++;
    }

    *finishd = avail - 1;
}

int main(){
    int starta, startb, finisha, finishb, startc, finishc, startd, finishd;
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

    mult_polynomial(starta, startb, finisha, finishb, &startc, &finishc, &startd, &finishd, &num_term);
    

    cout<<num_term<<endl;


    for(int i=startd; i<=finishd; i++){
        cout<<terms[i].coef<<" "<<terms[i].expon<<endl;
    }
    
    return 0;
}