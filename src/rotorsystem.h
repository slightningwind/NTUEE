#include <iostream>
#include <string>
#include "rotor.h"
using namespace std;

class rotorsystem{
private:
    rotor *first;
    rotor *last;
    string rotorlist;
    int syslength;

public:
    rotorsystem(string);
    void add_rotor(int);
    void build_rotors();
    void setpos(string);
    int encrypt(int);
    void rotate();
    string encryption(string);

};
