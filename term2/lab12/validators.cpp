#include <iostream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;


char inputValidatedChar(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.length() == 1 && isalpha(input[0])) {
            return tolower(input[0]);
        }
        cout << "Invalid input! Enter a single letter.\n";
    }
}

string inputValidatedWord(const string& prompt) {
    regex wordReg("^[a-zA-Z]+$");
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (regex_match(input, wordReg)) {
            return input;
        }
        cout << "Invalid input! Use letters only.\n";
    }
}

string inputValidatedString(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
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
