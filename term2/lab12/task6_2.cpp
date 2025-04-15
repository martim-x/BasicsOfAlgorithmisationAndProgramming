#include "word_hashtable.h"
#include "validators.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

void wordTableMenu() {
    int size = inputValidatedInt("Enter table size (10-10,000): ", 10, 10000);
    WordHashTable table(size);
    string filename;

    while (true) {
        cout << "\nWord Table Menu\n"
            << "1. Load file\n"
            << "2. Search word\n"
            << "3. Delete by initial\n"
            << "4. Show stats\n"
            << "5. Save to file\n"
            << "6. Exit\n";

        int choice = inputValidatedInt("Choose option (1-6): ", 1, 6);

        switch (choice) {
        case 1: {
            filename = "input_text.txt";
            ifstream file(filename);
            string word;
            while (file >> word) {
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                if (!word.empty()) table.insert(word);
            }
            break;
        }
        case 2: {
            string word = inputValidatedWord("Enter word: ");
            auto result = table.search(word);
            bool found = result.second;
            int comparisons = result.first;
            cout << (found ? "Found" : "Not found")
                << " | Comparisons: " << comparisons << "\n";
            break;
        }
        case 3: {
            char letter = inputValidatedChar("Enter initial letter: ");
            if (table.remove(letter)) {
                cout << "Removed all words starting with '" << letter << "'\n";
            }
            break;
        }
        case 4:
            table.display();
            break;
        case 5:
            table.saveToFile("output_text.txt");
            break;
        case 6:
            return;
        }
    }
}

int main() {
    wordTableMenu();
    return 0;
}