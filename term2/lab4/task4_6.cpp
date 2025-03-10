#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* next;
};


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


void add(Node*& head, int value) {
    Node* newNode = new Node{ value, nullptr };
    if (!head) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}


bool remove(Node*& head, int value) {
    Node* current = head, * prev = nullptr;
    while (current) {
        if (current->data == value) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}


bool contains(Node* head, int value) {
    while (head) {
        if (head->data == value) return true;
        head = head->next;
    }
    return false;
}


void print(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}


void saveToFile(Node* head, const string& filename) {
    ofstream file(filename);
    while (head) {
        file << head->data << " ";
        head = head->next;
    }
    file.close();
}


void loadFromFile(Node*& head, const string& filename) {
    ifstream file(filename);
    int value;
    while (file >> value) {
        add(head, value);
    }
    file.close();
}


void clear(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


void findSumNegativeTwoDigit(Node* head) {
    int sum = 0;
    bool found = false;
    while (head) {
        if (head->data < 0 && head->data <= -10 && head->data >= -99) {
            sum += head->data;
            found = true;
        }
        head = head->next;
    }
    if (found) {
        cout << "Sum of negative two-digit numbers: " << sum << endl;
    }
    else {
        cout << "No negative two-digit numbers found" << endl;
    }
}


void menu() {
    Node* head = nullptr;
    string filename;
    int choice, value;

    while (true) {
        cout << "\nMenu:\n"
            << "1. Add element\n"
            << "2. Delete element\n"
            << "3. Search element\n"
            << "4. Print list\n"
            << "5. Save to file\n"
            << "6. Load from file\n"
            << "7. Find sum neg\n"
            << "8. Exit\n"
            << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cin.ignore(INT32_MAX, '\n');
            value = inputValidatedInt("Enter a number (-1000 - 1000): ", -1000, 1000);
            add(head, value);
            break;

        case 2:
            cin.ignore(INT32_MAX, '\n');
            value = inputValidatedInt("Enter a number to delete (-1000 - 1000): ", -1000, 1000);
            if (remove(head, value)) {
                cout << "Element deleted" << endl;
            }
            else {
                cout << "Element not found" << endl;
            }
            break;

        case 3:
            cin.ignore(INT32_MAX, '\n');
            value = inputValidatedInt("Enter a number to search (-1000 - 1000): ", -1000, 1000);
            if (contains(head, value)) {
                cout << "Element found" << endl;
            }
            else {
                cout << "Element not found" << endl;
            }
            break;

        case 4:
            print(head);
            break;

        case 5:
            filename = "task4_8.bin";
            saveToFile(head, filename);
            break;

        case 6:
            filename = "task4_8.bin";
            clear(head);
            loadFromFile(head, filename);
            break;

        case 7:
            findSumNegativeTwoDigit(head);
            break;

        case 8:
            clear(head);
            return;

        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}