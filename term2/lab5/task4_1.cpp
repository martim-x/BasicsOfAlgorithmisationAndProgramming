#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"
using namespace std;


int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);

        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}

bool isValidInt(const string& promt, int value, int min, int max) {
    return value >= min && value <= max;
}


void splitStackBySign(Stack*& original, Stack*& Stack1, Stack*& Stack2) {
    while (original) {
        int value = original->data;
        pop(original);
        if (value > 0) {
            push(Stack1, value);
        }
        else if (value < 0) {
            push(Stack2, value);
        }
    }
}


#include "stack.h"

using namespace std;

int main() {
    Stack* stack = nullptr;
    Stack* stack1 = nullptr;
    Stack* stack2 = nullptr;
    string filename = "task4_1.bin";

    while (true) {
        cout << "\nStack Menu\n"
            << "1. Push\n"
            << "2. Pop\n"
            << "3. Show\n"
            << "4. Clear\n"
            << "5. Save to file\n"
            << "6. Load from file\n"
            << "7. Split stack\n"
            << "8. Exit\n"
            << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cin.ignore(INT16_MAX, '\n');
            value = inputValidatedInt("Enter value (-1000 - 1000): ", -1000, 1000);
            push(stack, value);
            break;
        }
        case 2:
            pop(stack);
            break;
        case 3:
            if (stack == nullptr) {
                cout << "Stack is empty." << endl;
            }
            else {
                cout << "Stack: ";
                show(stack);
            }

            if (stack1 != nullptr) {
                cout << "Stack1: ";
                show(stack1);
            }

            if (stack2 != nullptr) {
                cout << "Stack2: ";
                show(stack2);
            }
            break;
        case 4:
            clear(stack);
            clear(stack1);
            clear(stack2);
            break;
        case 5:
            saveToFile(stack, filename);
            break;
        case 6:
            loadFromFile(stack, filename);
            break;
        case 7:
            splitStackBySign(stack, stack1, stack2);
            cout << "Stack1 (values > 0): ";
            show(stack1);
            cout << "Stack2 (values < 0): ";
            show(stack2);
            break;
        case 8:
            clear(stack);
            clear(stack1);
            clear(stack2);
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

