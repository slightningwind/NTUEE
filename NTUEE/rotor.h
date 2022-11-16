#pragma once
class rotor{
private:
    int type;
    int pos;
    int anchor;
    int pattern[26];
    int invpattern[26];
    rotor *next;
    rotor *prev;
public:
    rotor();
    rotor(int);
    int crypt(int,int);
    friend class rotorsystem;
};
