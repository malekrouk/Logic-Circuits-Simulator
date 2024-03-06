#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <vector>
#include <iostream>
using namespace std;
class LogicGate {
private:
    vector<bool> inputs;
    int size;

public:
    LogicGate(vector<bool>& i);
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