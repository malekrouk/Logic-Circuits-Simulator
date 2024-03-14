//
// Created by Malek farouk on 14/03/2024.
//
/*
#ifndef LOGIC_CIRCUITS_SIMULATOR_GATES_H
#define LOGIC_CIRCUITS_SIMULATOR_GATES_H
#include <iostream>
#include <string>
#include <stack>
using namespace std;


class gates {
    int precedence(char c) {
        switch (c) {
            case '|':
                return 1;

            case '&':
                return 2;
            case '~':
                return 3;

        }
    }


    bool operandCheck(char c)
    {
        return ((c == '&') || (c == '~') || (c == '|'));
    }

    string infixToPostfix(string infix){
        int n=infix.size();
        stack<char> st;
        string postfix;
        for(int i=0;i<n;i++){
            if(operandCheck(infix[i])){
                //step 2
                postfix.push_back(infix[i]);
            }
            else if(infix[i] == '('){
                //step 3
                st.push('(');
            }
            else if(infix[i] == ')'){
                //step 4
                while( st.top() != '(' ){
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.pop();

            }
            else{
                //step 5
                while(!st.empty() && st.top() != '(' && precedence(st.top()) >= precedence(infix[i])){
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(infix[i]);
            }
        }

        while(!st.empty()){
            postfix.push_back(st.top());
            st.pop();
        }
        return postfix;
    }

};



#endif //LOGIC_CIRCUITS_SIMULATOR_GATES_H
