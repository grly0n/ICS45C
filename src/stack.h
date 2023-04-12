#include <iostream>
using namespace std;

constexpr int STK_MAX = 1000;

class Stack {
    int _top;
    char buf[STK_MAX];
public:
    Stack() {
        _top = -1;
    }

    void push(char c) {
        if (_top != STK_MAX-1) {
            _top++;
            buf[_top] = c;
        } else {
            cout << "error: cannot push into full stack." << endl;
        }
    }

    char pop() {
        if (_top == -1) {
            return '@';
        } else {
            char t = buf[_top];
            buf[_top] = ' ';
            _top--;
            return t;
        }
    }

    char top() {
        if (_top == -1) {
            return '@';
        } else {
            return buf[_top];
        }
    }

    bool isEmpty() {
        if (_top == -1) {
            return true;
        } else {
            return false;
        }
    }

    bool isFull() {
        if (_top == STK_MAX-1) {
            return true;
        } else {
            return false;
        }
    }
};

void push_all(Stack &stk, string line) {
    for (int i = 0; i < line.size(); i++) {
        stk.push(line[i]);
    }
}

void pop_all(Stack &stk) {
    while (!stk.isEmpty()) {
        cout << stk.pop();
    }
    cout << endl;
}
