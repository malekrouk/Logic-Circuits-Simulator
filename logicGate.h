/*
#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <vector>
#include <iostream>
using namespace std;
class LogicGate {
private:
    vector<bool> inputs; //We use vectors in order to be able to handle any user defined
    int size;            //number of inputs into a gate. Meaning the size of the vector
    // represents the number of inputs into a gate, with each index having one input.


public:
    LogicGate(vector<bool>& i); //constructor

    // the gates
    bool AND() const;
    bool NAND() const;
    void BUFFER();
    bool OR() const;
    bool NOR() const;
    bool XOR();
    bool XNOR();
    void NOT();
};

#endif