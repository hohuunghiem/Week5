#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    int key;
    Node* prev;
    Node* next;
};

struct Stack {
    Node* top;
};

Stack* initializeStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    return s;
}

bool isEmpty(Stack* s) {
    if (s->top == nullptr) return true;
    return false;
}

Node* createNode(int data) {
    Node* temp = new Node;
    temp->key = data;
    temp->prev = nullptr;
    temp->next = nullptr;
    return temp;
}

void push(Stack*& s, int key) {
    Node* p = createNode(key);
    if (s->top != nullptr) {
        p->next = s->top;
        s->top->prev = p;
    }
    s->top = p;
}

int pop(Stack*& s) {
    if (s->top == nullptr) {
        return -1;
    }
    Node* temp = s->top;
    int result = temp->key;
    s->top = s->top->next;
    if (s->top != nullptr) {
        s->top->prev = nullptr;
    }
    delete temp;
    return result;
}

void printStack(Stack* s, ofstream& outfile) {
    if (s->top == nullptr) {
        outfile << "EMPTY" << endl;
        return;
    }
    Node* cur = s->top;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    while (cur != nullptr) {
        outfile << cur->key << " ";
        cur = cur->prev;
    }
    outfile << endl;
}

void clearStack(Stack*& s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}
int size(Stack* s) {
    int result = 0;
    Node* cur = s->top;
    while (cur != nullptr) {
        result++;
        cur = cur->next;
    }
    return result;
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    if (!infile) {
        cerr << "Can't open file input.txt" << endl;
        return -1;
    }
    if (!outfile) {
        cerr << "Can't open file output.txt" << endl;
        return -1;
    }
    Stack* s = new Stack;
    string cmd;

    while (infile >> cmd) {
        if (cmd == "init") {
            s = initializeStack();
        }
        else if (cmd == "push") {
            int x;
            infile >> x;
            push(s, x);
        }
        else if (cmd == "pop") {
            pop(s);
        }
        printStack(s, outfile);
    }

    infile.close();
    outfile.close();
    return 0;
}
