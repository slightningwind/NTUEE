#include "functions.h"

int ltn(char input){
    return (int)input-97;
}

char ntl(int input){
    return (char)(input+97);
}

int add(int a,int b){
    if(a+b>=26){
        return a+b-26;
    }
    else{
        return a+b;
    }
}
int subtract(int a,int b){
    if(a-b<0){
        return a-b+26;
    }
    else{
        return a-b;
    }
}
