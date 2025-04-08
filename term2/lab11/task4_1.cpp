#include "hash_table.h"
#include <iostream>
#include <string>
using namespace std;

int getValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(INT32_MAX, '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        cin.clear();
        cin.ignore(INT32_MAX, '\n');
    }
}

string getValidatedString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Invalid input. Please enter a non-empty string." << endl;
    }
}

void displayMenu() {
    cout << "\nHash Table with Quadratic Probing Menu:" << endl;
    cout << "1. Insert key-value pair" << endl;
    cout << "2. Remove by key" << endl;
    cout << "3. Search by key" << endl;
    cout << "4. Display table contents" << endl;
    cout << "5. Display table statistics" << endl;
    cout << "6. Clear table" << endl;
    cout << "7. Measure search time" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    cout << "This implementation uses h(key, i) = (h'(key) + c1*i + c2*i^2) mod size" << endl;
    
    int size = getValidatedInt("Enter initial table size (1-1000): ", 1, 1000);
    
    HashTable table(size, HashType::QUADRATIC);
    
    while (true) {
        displayMenu();
        int choice = getValidatedInt("Enter your choice (0-7): ", 0, 7);
        
        switch (choice) {
            case 1: {
                int keyInt = getValidatedInt("Enter key (any positive number): ", 1, INT32_MAX);
                string key = to_string(keyInt);
                string value = getValidatedString("Enter value: ");
                table.insert(key, value);
                cout << "Key-value pair inserted successfully." << endl;
                break;
            }
            case 2: {
                int keyInt = getValidatedInt("Enter key to remove (any positive number): ", 1, INT32_MAX);
                string key = to_string(keyInt);
                table.remove(key);
                cout << "Key removed successfully." << endl;
                break;
            }
            case 3: {
                int keyInt = getValidatedInt("Enter key to search (any positive number): ", 1, INT32_MAX);
                string key = to_string(keyInt);
                string result = table.search(key);
                if (!result.empty()) {
                    cout << "Value found: " << result << endl;
                } else {
                    cout << "Key not found." << endl;
                }
                break;
            }
            case 4: {
                cout << "\nHash Table Contents:" << endl;
                table.display();
                break;
            }
            case 5: {
                cout << "\nHash Table Statistics:" << endl;
                table.displayStats();
                break;
            }
            case 6: {
                table.clear();
                cout << "Table cleared successfully." << endl;
                break;
            }
            case 7: {
                int keyInt = getValidatedInt("Enter key to measure search time (any positive number): ", 1, INT32_MAX);
                string key = to_string(keyInt);
                table.measureSearchTime(key);
                break;
            }
            case 0: {
                return 0;
            }
        }
    }
    
    return 0;
} 