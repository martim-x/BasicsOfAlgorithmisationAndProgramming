#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>

struct Stack {
    int data;
    Stack* next;
};

void push(Stack*& top, int value);
void pop(Stack*& top);
void show(Stack* top);
void clear(Stack*& top);
void saveToFile(Stack* top, const std::string& filename);
void loadFromFile(Stack*& top, const std::string& filename);
void splitStack(Stack*& original, Stack*& Stack1, Stack*& Stack2);

#endif
