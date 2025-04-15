#include "chainhashtable.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <regex>
#include <string>

using namespace std;
using namespace std::chrono;

void displayMenu() {
    cout << "\nAirport Hash Table Management\n";
    cout << "1. Add Flight\n";
    cout << "2. Remove Flight\n";
    cout << "3. Search Flight\n";
    cout << "4. Display All\n";
    cout << "5. Clear Table\n";
    cout << "6. Exit\n";
}

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

bool isValidCountryOrTownName(const string& name) {
    if (name.empty()) return false;
    regex namePattern(R"(^[A-Z][a-z]+(?:[ -][A-Z][a-z]+)?$)");

    if (regex_match(name, namePattern))
        return true;

    return false;
}

string inputValidatedCountryOrTownName(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);

        if (isValidCountryOrTownName(name)) return name;

        cout << "Invalid input!\n";
    }
}



int main() {
    int capacity = inputValidatedInt("Enter hash table size (1-1000): ", 1, 1000);
    ChainHashTable ht(capacity);

    while (true) {
        displayMenu();
        int choice = inputValidatedInt("Choose option: ", 1, 6);

        switch (choice) {
        case 1: {
            int num = inputValidatedInt("Enter flight number (1-9999): ", 1, 9999);
            string dest = inputValidatedCountryOrTownName("Destination: ");
            ht.insert(num, dest);
            cout << "Flight added!\n";
            break;
        }
        case 2: {
            int num = inputValidatedInt("Enter flight number to remove: ", 1, 9999);
            if (ht.remove(num)) cout << "Flight removed!\n";
            else cout << "Flight not found!\n";
            break;
        }
        case 3: {
            int num = inputValidatedInt("Enter flight number to search: ", 1, 9999);
            auto start = high_resolution_clock::now();
            string dest = ht.search(num);
            auto end = high_resolution_clock::now();

            if (!dest.empty()) {
                cout << "Destination: " << dest << "\n";
            }
            else {
                cout << "Flight not found!\n";
            }
            cout << "Search time: "
                << duration_cast<microseconds>(end - start).count()
                << " microseconds\n";
            break;
        }
        case 4:
            ht.display();
            break;
        case 5:
            ht.clear();
            cout << "Table cleared!\n";
            break;
        case 6:
            return 0;
        }
    }
}