#include "hash_table.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

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
    cout << prompt;
    getline(cin, value);
    return value;
}


string generateRandomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    string result;
    for (int i = 0; i < length; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return result;
}

void displayMenu() {
    cout << "\nHash Table with Universal/Modular Hashing Menu:" << endl;
    cout << "1. Insert key-value pair" << endl;
    cout << "2. Remove by key" << endl;
    cout << "3. Search by key" << endl;
    cout << "4. Display table contents" << endl;
    cout << "5. Display table statistics" << endl;
    cout << "6. Clear table" << endl;
    cout << "7. Test search performance" << endl;
    cout << "0. Exit" << endl;
}

void testSearchPerformance(HashType type) {
    cout << "\nTesting " << (type == HashType::OPEN_ADDRESS ? "Modular" : "Universal") << " Hashing Performance:" << endl;
    cout << "Creating test hash table..." << endl;
    HashTable testTable(100010, type);
    
    cout << "Generating 100000 random elements..." << endl;
    vector<string> testKeys;
    
    // Generate and save keys
    for (int i = 0; i < 100000; ++i) {
        string key = generateRandomString(10);
        string value = generateRandomString(20);
        testKeys.push_back(key);
        testTable.insert(key, value);
    }
    
    cout << "Testing search performance with 1000 random elements..." << endl;
    double totalTime = 0;
    
    // Test with 1000 random keys
    for (int i = 0; i < 1000; ++i) {
        string key = testKeys[rand() % testKeys.size()];
        
        auto start = chrono::high_resolution_clock::now();
        testTable.search(key);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        totalTime += duration.count();
    }

    cout << "Average search time: " << totalTime / 1000 << " milliseconds" << endl;
    cout << "Table statistics:" << endl;
    testTable.displayStats();
}

int main() {
    srand(time(nullptr));
    
    cout << "Hash Table Implementation" << endl;
    cout << "Select hash function type:" << endl;
    cout << "1. Modular Hashing" << endl;
    cout << "2. Universal Hashing" << endl;
    
    int hashTypeChoice = getValidatedInt("Enter your choice (1-2): ", 1, 2);
    HashType type = (hashTypeChoice == 1) ? HashType::OPEN_ADDRESS : HashType::UNIVERSAL;
    
    int size = getValidatedInt("Enter initial table size (1-1000): ", 1, 1000);
    HashTable table(size, type);
    
    while (true) {
        displayMenu();
        int choice = getValidatedInt("Enter your choice (0-8): ", 0, 8);
        
        switch (choice) {
            case 1: {
                string key = getValidatedString("Enter key: ");
                string value = getValidatedString("Enter value: ");
                table.insert(key, value);
                cout << "Key-value pair inserted successfully." << endl;
                break;
            }
            case 2: {
                string key = getValidatedString("Enter key to remove: ");
                table.remove(key);
                cout << "Key removed successfully." << endl;
                break;
            }
            case 3: {
                string key = getValidatedString("Enter key to search: ");
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
                cout << "\n=== Performance Testing ===" << endl;
                cout << "Testing both hash functions..." << endl;
                
                // Test Modular Hashing
                testSearchPerformance(HashType::OPEN_ADDRESS);
                
                cout << "\n---" << endl;
                
                // Test Universal Hashing
                testSearchPerformance(HashType::UNIVERSAL);
                
                cout << "\n=== Performance Testing Complete ===" << endl;
                break;
            }
            case 0: {
                return 0;
            }
        }
    }
    
    return 0;
} 