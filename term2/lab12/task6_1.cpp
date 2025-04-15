#include "char_hashtable.h"
#include "validators.h"
#include <iostream>
#include <string>
using namespace std;

void charCounterMenu() {
    CharHashTable table(256);
    string input;

    while (true) {
        cout << "\nCharacter Counter Menu\n"
            << "1. Input text\n"
            << "2. Show counts\n"
            << "3. Search letter\n"
            << "4. Exit\n";

        int choice = inputValidatedInt("Choose option (1-4): ", 1, 4);

        switch (choice) {
        case 1: {
            cout << "Enter text: ";
            getline(cin, input);
            table.clear();
            for (char c : input) {
                if (isalpha(c)) table.insert(c);
            }
            break;
        }
        case 2:
            table.display();
            break;
        case 3: {
            char letter = inputValidatedChar("Enter letter: ");
            cout << "Count: " << table.search(letter) << "\n";
            break;
        }
        case 4:
            return;
        }
    }
}

int main() {
    charCounterMenu();
    return 0;
}