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


void removeMultiplesOfThree(Stack*& stack) {
    Stack* prev = nullptr;
    Stack* current = stack;

    while (current) {
        if (current->data % 3 == 0) {
            Stack* temp = current;
            current = current->next;

            if (prev) {
                prev->next = current;
            }
            else {
                stack = current;
            }

            delete temp;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

#include "stack.h"

using namespace std;

int main() {
    Stack* stack = nullptr;
    string filename = "task4_11.bin";

    while (true) {
        cout << "\nStack Menu\n"
            << "1. Push\n"
            << "2. Pop\n"
            << "3. Show\n"
            << "4. Clear\n"
            << "5. Save to file\n"
            << "6. Load from file\n"
            << "7. Remove Elements Devideable By Three\n"
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
            break;
        case 4:
            clear(stack);

            break;
        case 5:
            saveToFile(stack, filename);
            break;
        case 6:
            loadFromFile(stack, filename);
            break;
        case 7:
            removeMultiplesOfThree(stack);
            break;
        case 8:
            clear(stack);
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

