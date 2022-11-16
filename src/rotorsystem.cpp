#include <iostream>
#include <string>
#include "rotor.h"
#include "functions.h"
#include "rotorsystem.h"

rotorsystem::rotorsystem(string list){
    rotorlist=list;
    first=0;
    last=0;
    syslength=list.length();
}
void rotorsystem::add_rotor(int type){
    rotor *newrotor = new rotor(type);
    if(first==0){
        first=newrotor;
        last=newrotor;
        return;
    }
    newrotor->prev=last;
    last->next=newrotor;
    last=newrotor;
}

void rotorsystem::build_rotors(){
    int k=syslength;
    for(int i=0;i<k;i++){
        add_rotor(ltn(rotorlist[i]));
    }
    add_rotor(26);
}

void rotorsystem::setpos(string poscode){
    int a=poscode.length();
    rotor *current=first;
    for(int i=0;i<a;i++){
        current->pos=ltn(poscode[i]);
        current=current->next;
    }
}

int rotorsystem::encrypt(int input){
    rotor *current=first;
    for(int i=0;i<syslength;i++){
        input=current->crypt(1,input);
        current=current->next;
    }
    input=current->crypt(1,input);
    current=current->prev;
    for(int i=0;i<syslength;i++){
        input=current->crypt(-1,input);
        current=current->prev;
    }
    return input;
}

string rotorsystem::encryption(string input){
    string output="";
    int il=input.length();
    for(int i=0;i<il;i++){
        int j=ltn(input[i]);
        j=encrypt(j);
        output+=ntl(j);
    }
    return output;
}

void rotorsystem::rotate(){
    rotor *current=first;
    for(int i=0;i<syslength;i++){
        if(current->pos==current->anchor){
            add(current->pos,1);
            current=current->next;
            continue;
        }
        else{
            add(current->pos,1);
            break;
        }
    }
}
