#include "hash_table.h"
#include <iostream>
#include <string>
#include <climits>
#include <random>
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
    cout << "\nHash Table Comparison Menu:" << endl;
    cout << "1. Insert key-value pair (Universal Hashing)" << endl;
    cout << "2. Insert key-value pair (Modular Hashing)" << endl;
    cout << "3. Remove by key" << endl;
    cout << "4. Search by key" << endl;
    cout << "5. Display table contents" << endl;
    cout << "6. Display table statistics" << endl;
    cout << "7. Clear table" << endl;
    cout << "8. Compare search times" << endl;
    cout << "9. Exit" << endl;
}

void compareSearchTimes(HashTable& universalTable, HashTable& modularTable, int size) {
    cout << "\nComparing search times between Universal and Modular Hashing:" << endl;
    
    // Generate random keys for comparison
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size-1);
    
    for (int i = 0; i < 5; i++) {
        int key = dis(gen);
        cout << "\nSearching for key " << key << ":" << endl;
        
        cout << "Universal Hashing: ";
        universalTable.measureSearchTime(key);
        
        cout << "Modular Hashing: ";
        modularTable.measureSearchTime(key);
    }
}

int main() {
    cout << "Welcome to Hash Table Comparison Implementation!" << endl;
    cout << "This implementation compares Universal and Modular Hashing" << endl;
    
    // Get initial table size
    int size = getValidatedInt("Enter initial table size (1-1000): ", 1, 1000);
    
    // Create tables with different hash types
    HashTable universalTable(size, HashType::UNIVERSAL);
    HashTable modularTable(size, HashType::LINEAR);
    
    while (true) {
        displayMenu();
        int choice = getValidatedInt("Enter your choice (1-9): ", 1, 9);
        
        switch (choice) {
            case 1: {
                int key = getValidatedInt("Enter key (0-" + to_string(size-1) + "): ", 0, size-1);
                string value = getValidatedString("Enter value: ");
                universalTable.insert(key, value);
                cout << "Key-value pair inserted successfully in Universal Hashing table." << endl;
                break;
            }
            case 2: {
                int key = getValidatedInt("Enter key (0-" + to_string(size-1) + "): ", 0, size-1);
                string value = getValidatedString("Enter value: ");
                modularTable.insert(key, value);
                cout << "Key-value pair inserted successfully in Modular Hashing table." << endl;
                break;
            }
            case 3: {
                int key = getValidatedInt("Enter key to remove (0-" + to_string(size-1) + "): ", 0, size-1);
                universalTable.remove(key);
                modularTable.remove(key);
                cout << "Key removed successfully from both tables." << endl;
                break;
            }
            case 4: {
                int key = getValidatedInt("Enter key to search (0-" + to_string(size-1) + "): ", 0, size-1);
                string result1 = universalTable.search(key);
                string result2 = modularTable.search(key);
                cout << "Universal Hashing: " << (result1.empty() ? "Not found" : "Found: " + result1) << endl;
                cout << "Modular Hashing: " << (result2.empty() ? "Not found" : "Found: " + result2) << endl;
                break;
            }
            case 5: {
                cout << "\nUniversal Hashing Table Contents:" << endl;
                universalTable.display();
                cout << "\nModular Hashing Table Contents:" << endl;
                modularTable.display();
                break;
            }
            case 6: {
                cout << "\nUniversal Hashing Table Statistics:" << endl;
                universalTable.displayStats();
                cout << "\nModular Hashing Table Statistics:" << endl;
                modularTable.displayStats();
                break;
            }
            case 7: {
                universalTable.clear();
                modularTable.clear();
                cout << "Both tables cleared successfully." << endl;
                break;
            }
            case 8: {
                compareSearchTimes(universalTable, modularTable, size);
                break;
            }
            case 9: {
                cout << "Thank you for using Hash Table Comparison. Goodbye!" << endl;
                return 0;
            }
        }
    }
    
    return 0;
} 