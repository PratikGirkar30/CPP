/* Implement stack as an abstract data type using singly linked list and use this ADT for conversion of
infix expression to postfix, prefix and evaluation of postfix and prefix expression. 
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }
    void push(char value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }
    char pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        char value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    char peek() {
        if (top == nullptr) {
            return '\0';
        }
        return top->data;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop(); 
        }
        else if (isOperator(ch)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.isEmpty()) {
        postfix += s.pop();
    }
    return postfix;
}

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int evaluatePostfix(string postfix) {
    Stack s;
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            s.push(ch - '0'); 
        }
        else if (isOperator(ch)) {
            int operand2 = s.pop();
            int operand1 = s.pop();
            int result = 0;
            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = pow(operand1, operand2); break;
            }
            s.push(result);
        }
    }
    return s.pop();
}

int evaluatePrefix(string prefix) {
    Stack s;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isdigit(ch)) {
            s.push(ch - '0'); 
        }
        else if (isOperator(ch)) {
            int operand1 = s.pop();
            int operand2 = s.pop();
            int result = 0;
            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = pow(operand1, operand2); break;
            }
            s.push(result);
        }
    }
    return s.pop();
}

int main() {
    string infix = "(A+B)*(C-D)";
    cout << "Infix Expression: " << infix << endl;
    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;
    string prefix = infixToPrefix(infix);
    cout << "Prefix Expression: " << prefix << endl;
    string postfixEval = "23*5+";
    cout << "Postfix Evaluation: " << evaluatePostfix(postfixEval) << endl;
    string prefixEval = "*+23-45";
    cout << "Prefix Evaluation: " << evaluatePrefix(prefixEval) << endl;

    return 0;
}
