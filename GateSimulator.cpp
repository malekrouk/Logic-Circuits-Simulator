//
// Created by Malek farouk on 14/03/2024.
//
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class LogicGateExpressionEvaluator {
private:
    int precedence(char ch) {
        switch(ch) {
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

    string infixToPostfix(const string& infix) { //infix to postfix using stack
        stack<char> st; //create stack
        string postfix;

        for (char c : infix) {
            if (isOperator(c)) { //check for operator
                while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
            } else {
                postfix += c;
            }
        }

        while (!st.empty()) {
            postfix += st.top();
            st.pop();
        }

        return postfix;
    }

    bool evaluatePostfix(const string& postfix, bool i1, bool i2) {
        stack<bool> st;

        for (char c : postfix) {
            if (!isOperator(c)) {
                st.push(c == 'i' ? i1 : i2);
            } else {
                if (c == '~') {
                    bool operand = st.top();
                    st.pop();
                    st.push(!operand);
                } else {
                    bool operand2 = st.top();
                    st.pop();
                    bool operand1 = st.top();
                    st.pop();
                    switch (c) {
                        case '&':
                            st.push(operand1 && operand2);
                            break;
                        case '|':
                            st.push(operand1 || operand2);
                            break;
                    }
                }
            }
        }

        return st.top();
    }

public:
    bool evaluateExpression(const string& expression, bool i1, bool i2) {
        string postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix, i1, i2);
    }
};

int main() {
    LogicGateExpressionEvaluator evaluate;

    bool i1, i2;
    string expression;
    
    i1 = true;
    i2 = false;
    expression = "i1&~i2";
    cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;

    expression = "~i1|i2";
    std::cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;

    expression = "i1&i2|~i1";
    std::cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;

    return 0;
}


