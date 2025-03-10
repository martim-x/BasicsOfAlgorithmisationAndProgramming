#include "stack.h"

using namespace std;

void push(Stack*& top, int value) {
    Stack* newNode = new Stack{ value, top };
    top = newNode;
}

void pop(Stack*& top) {
    if (top == nullptr) {
        cout << "Stack is empty!" << endl;
        return;
    }
    Stack* temp = top;
    top = top->next;
    delete temp;
}

void show(Stack* top) {
    Stack* current = top;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void clear(Stack*& top) {
    while (top) {
        pop(top);
    }
}

void saveToFile(Stack* top, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Stack* current = top;
    while (current) {
        file.write(reinterpret_cast<char*>(&current->data), sizeof(int));
        current = current->next;
    }

    cout << "Stack saved to " << filename << endl;
}

void loadFromFile(Stack*& top, const string& filename) {
    clear(top);
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        push(top, value);
    }

    cout << "Stack loaded from " << filename << endl;
}

