/*
#include "logicGate.h"
#include <unistd.h>

LogicGate::LogicGate(vector<bool> &i)
{
    inputs = i;
    size = i.size();
}



bool LogicGate::AND() const {
    for (int i = 0; i < size; i++) {
        if (!inputs[i])
            return false;
    }
    return true;
}

bool LogicGate::NAND() const {
    return !AND();
}

void LogicGate::BUFFER() {
    sleep(50);
}

bool LogicGate::OR() const {
    for (int i = 0; i < size; i++) {
        if (inputs[i])
            return true;
    }
    return false;
}

bool LogicGate::NOR() const {
    return !OR();
}

bool LogicGate::XOR() {
    bool v = inputs[0];
    for (int i = 1; i < size; i++) {
        if (inputs[i] != v)
            return true;
    }
    return false;
}

bool LogicGate::XNOR() {
    return !XOR();
}

void LogicGate::NOT() {
    for (int i = 0; i < size; i++)
        inputs[i] = !inputs[i];
}