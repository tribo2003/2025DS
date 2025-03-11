#define MAX_TERMS 200  
/*size of terms array*/ 
typedef struct{ 
    float coef; 
    int expon;
}polynomial; 
polynomial terms [MAX_TERMS]; 

int attach(float coeff, int expone){
    if(avail>=MAX_TERMS){
        cout>>"too many terms">>endl;
    }
    terms[avail].coef=coeff;
    terms[avail].expon=expone;
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
int sub_polynomial(int starta, int startb, int finisha, int finishb, int* startd, int* finishd){
    float coeff;
    *startd=avail;
    while((starta<=finisha)&&(startb<=finishb)){
        switch(compare(terms[starta].expon,terms[startb].expon)){
            case -1: //a<b
                attach((-terms[startb].coef),terms[starta].expon)
                startb++;
                break;
            case 0: //a=b
                starta++;
                startb++;
                break;
            case 1: //a>b
                attach(terms[starta].coef,terms[starta].expon);
                starta++;
        }
    }

    for(; starta<=finisha; starta++){
        attach(terms[starta].coef,terms[starta].expon);
    }
    for(; startb<=finishb; startb++){
        attach(terms[startb].coef, terms[startb].expon);
    }
    *finishd=avail-1;
}

int main(){
    int starta, startb, finisha, finishb, startd, finishd;
    int m, n;
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>terms.coef;
        cin>>terms.expon;
    }
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>terms.coef;
        cin>>terms.expon;
    }



}