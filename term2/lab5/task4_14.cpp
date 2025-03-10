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


void findDuplicates(Stack* stack1, Stack* stack2, Stack*& stack) {
    Stack* temp1 = stack1;
    while (temp1) {
        Stack* temp2 = stack2;
        while (temp2) {
            if (temp1->data == temp2->data) {
                Stack* check = stack;
                bool found = false;
                while (check) {
                    if (check->data == temp1->data) {
                        found = true;
                        break;
                    }
                    check = check->next;
                }
                if (!found) {
                    push(stack, temp1->data);
                }
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}



#include "stack.h"

using namespace std;

int main() {
    Stack* stack = nullptr;
    Stack* stack1 = nullptr;
    Stack* stack2 = nullptr;
    string filename = "task4_14.bin";

    while (true) {
        cout << "\nStack Menu\n"
            << "1. Push\n"
            << "2. Pop\n"
            << "3. Show\n"
            << "4. Clear\n"
            << "5. Save to file\n"
            << "6. Load from file\n"
            << "7. Find Duplicates stack\n"
            << "8. Exit\n"
            << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            int sub_choice;
            cout << "1. Push to Stack1\n"
                << "2. Push to Stack2\n";
            cin >> sub_choice;
            switch (sub_choice) {
            case 1:
                cin.ignore(INT16_MAX, '\n');
                value = inputValidatedInt("Enter value (-1000 - 1000): ", -1000, 1000);
                push(stack1, value);
                break;

            case 2:
                cin.ignore(INT16_MAX, '\n');
                value = inputValidatedInt("Enter value (-1000 - 1000): ", -1000, 1000);
                push(stack2, value);
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

            break;
        }
        case 2:
            int sub_choice;
            cout << "1. Pop Stack1\n"
                << "2. Pop Stack2\n"
                << "3. Pop Stack\n";
            cin >> sub_choice;
            switch (sub_choice) {
            case 1:
                pop(stack1);
                break;

            case 2:
                pop(stack2);
                break;

            case 3:
                pop(stack);
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

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
            findDuplicates(stack1, stack2, stack);
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

