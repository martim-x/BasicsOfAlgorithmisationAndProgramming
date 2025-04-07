#include "hash_table.h"
#include <iostream>
#include <string>
#include <climits>
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
    cout << "\nHash Table Collision Resolution Methods Menu:" << endl;
    cout << "1. Insert key-value pair" << endl;
    cout << "2. Remove by key" << endl;
    cout << "3. Search by key" << endl;
    cout << "4. Display table contents" << endl;
    cout << "5. Display table statistics" << endl;
    cout << "6. Clear table" << endl;
    cout << "7. Measure search time" << endl;
    cout << "8. Test all collision resolution methods" << endl;
    cout << "9. Exit" << endl;
}

void testAllMethods(int size) {
    HashType types[] = {HashType::LINEAR, HashType::QUADRATIC, HashType::DOUBLE, HashType::UNIVERSAL};
    string names[] = {"Linear Probing", "Quadratic Probing", "Double Hashing", "Universal Hashing"};
    
    for (int i = 0; i < 4; i++) {
        cout << "\nTesting " << names[i] << ":" << endl;
        cout << "=================================" << endl;
        
        HashTable table(size, types[i]);
        
        // Insert elements that will cause collisions
        for (int j = 0; j < size * 0.8; j++) {
            int key = j * 10; // All keys are multiples of 10 to cause collisions
            table.insert(key, "Value" + to_string(key));
        }
        
        // Display statistics
        table.displayStats();
        
        // Measure search times
        cout << "\nMeasuring search times:" << endl;
        table.measureSearchTime(0);    // First element
        table.measureSearchTime(size/2 * 10);  // Middle element
        table.measureSearchTime((size-1) * 10);  // Last element
        table.measureSearchTime(size * 10);  // Non-existent element
    }
}

int main() {
    cout << "Welcome to Hash Table Collision Resolution Methods Implementation!" << endl;
    
    // Get initial table size
    int size = getValidatedInt("Enter initial table size (1-1000): ", 1, 1000);
    
    // Get hash type
    cout << "\nSelect Collision Resolution Method:" << endl;
    cout << "1. Linear Probing" << endl;
    cout << "2. Quadratic Probing" << endl;
    cout << "3. Double Hashing" << endl;
    cout << "4. Universal Hashing" << endl;
    int hashTypeChoice = getValidatedInt("Select method (1-4): ", 1, 4);
    
    HashType type;
    switch (hashTypeChoice) {
        case 1: type = HashType::LINEAR; break;
        case 2: type = HashType::QUADRATIC; break;
        case 3: type = HashType::DOUBLE; break;
        case 4: type = HashType::UNIVERSAL; break;
    }
    
    HashTable table(size, type);
    
    while (true) {
        displayMenu();
        int choice = getValidatedInt("Enter your choice (1-9): ", 1, 9);
        
        switch (choice) {
            case 1: {
                int key = getValidatedInt("Enter key (0-" + to_string(size-1) + "): ", 0, size-1);
                string value = getValidatedString("Enter value: ");
                table.insert(key, value);
                cout << "Key-value pair inserted successfully." << endl;
                break;
            }
            case 2: {
                int key = getValidatedInt("Enter key to remove (0-" + to_string(size-1) + "): ", 0, size-1);
                table.remove(key);
                cout << "Key removed successfully." << endl;
                break;
            }
            case 3: {
                int key = getValidatedInt("Enter key to search (0-" + to_string(size-1) + "): ", 0, size-1);
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
                int key = getValidatedInt("Enter key to measure search time (0-" + to_string(size-1) + "): ", 0, size-1);
                table.measureSearchTime(key);
                break;
            }
            case 8: {
                testAllMethods(size);
                break;
            }
            case 9: {
                cout << "Thank you for using Hash Table Implementation. Goodbye!" << endl;
                return 0;
            }
        }
    }
    
    return 0;
} 