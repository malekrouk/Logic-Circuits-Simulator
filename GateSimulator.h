//
// Created by Malek farouk on 14/03/2024.
//
#pragma once
#include <iostream>
#include <stack>
#include <string>
using namespace std;
class LogicGateExpressionEvaluator {
private:
    int precedence(char c) {
        switch (c) {
        case '&': //2nd highest precedence
            return 2;
        case '|': //lowest precedence
            return 1;
        case '~': //highest precedence
            return 3;
        default:
            return -1;
        }
    }

    bool isOperator(char c) { //spot operator
        return (c == '&' || c == '|' || c == '~');
    }

    //convert infix boolean expression to postfix
    string infixToPostfix(const string& infix) {
        stack<char> st; //create stack
        string postfix;

        //loop over every char in infix expression
        for (char c : infix) {
            if (isOperator(c)) {
                //process operators and manage precedence
                while (!st.empty() && st.top() != '(' && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top(); //add operators from the stack to the postfix expression if they have higher or equal precedence
                    st.pop(); //pop the operators from the stack
                }
                st.push(c);
            }
            else if (c == '(') {
                st.push(c); //push ( onto the stack
            }
            else if (c == ')') {

                while (!st.empty() && st.top() != '(') {
                    postfix += st.top(); //add operators until an opening parenthesis is found
                    st.pop(); //pop the operators from the stack
                }
                st.pop(); //remove opening parenthesis
            }
            else { //if the character is a variable
                postfix += c; // add the variable to the postfix expression
            }
        }

        //remaining operators on the stack
        while (!st.empty()) {
            postfix += st.top(); // add operators to the postfix expression
            st.pop(); //pop the operators from the stack
        }

        return postfix;
    }


    bool evaluatePostfix(const string& postfix, bool i1, bool i2) {
        stack<bool> st; //stack to hold the variables during evaluation
        bool insideParentheses = false;

        //loop over each character in the postfix expression
        for (char c : postfix) {
            if (c == '(') {
                insideParentheses = true;
            }
            else if (c == ')') {
                insideParentheses = false;
            }
            else if (!isOperator(c)) { //if the character is a variable

                bool value = (c == '1');
                if (value) { //variable c is true
                    st.push(i1);
                }
                else {
                    st.push(i2);
                }
            }
            else { //if the character is a operator
                if (c == '~') {
                    if (insideParentheses) {
                        //negate the entire subexpression within parentheses
                        while (!st.empty() && st.top() != '(') {
                            bool variable = st.top();
                            st.pop();
                            st.push(!variable);
                        }
                        //pop (
                        if (!st.empty() && st.top() == '(') {
                            st.pop();
                        }
                    }
                    else { //not inside parentheses
                        //negate the top variable
                        if (!st.empty()) {
                            bool variable = st.top();
                            st.pop();
                            st.push(!variable);
                        }
                    }
                }
                else { //if the operator is (AND or OR)

                    if (!st.empty()) {
                        bool variable2 = st.top(); //second variable
                        st.pop(); // Pop the second variable from the stack
                        if (!st.empty()) {
                            bool variable1 = st.top(); //first variable
                            st.pop();
                            switch (c) {
                            case '&':
                                st.push(variable1 && variable2); //push result of AND operation onto the stack
                                break;
                            case '|':
                                st.push(variable1 || variable2); //push result of OR operation onto the stack
                                break;
                            }
                        }
                    }
                }
            }
        }

        //return result of expression if the stack is not empty
        if (!st.empty())
            return st.top();
        else
            return false;

    }



public:
    bool evaluateExpression(const string& expression, bool i1, bool i2) {
        string postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix, i1, i2);
    }
};


