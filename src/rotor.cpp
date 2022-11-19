#include <iostream>
#include "rotor.h"
#include "data.h"
#include "functions.h"
using namespace std;

rotor::rotor(){
    type=0;
    pos=0;
    notch=0;
    next=0;
    prev=0;
}

rotor::rotor(int input){
    type=input;
    pos=0;
    if(input==26){
        notch=0;
    }
    else{
        notch=get_notch(input);
    }
    for(int i=0;i<26;i++){
        if(input==26){
            pattern[i]=refl_data(i);
            invpattern[i]=refl_data(i);
        }
        else{
            pattern[i]=get_data(1,input,i);
            invpattern[i]=get_data(-1,input,i);
        }

    }
    next=0;
    prev=0;
}

int rotor::crypt(int direc, int input){
    input=add(input,pos);
    switch(direc){
        case 1:
            input=pattern[input];
            break;
        case -1:
            input=invpattern[input];
            break;
    }
    input=subtract(input,pos);
    return input;
}
