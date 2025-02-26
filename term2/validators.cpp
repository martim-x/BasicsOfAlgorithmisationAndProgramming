#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <iostream>
using namespace std;


int inputValidatedInt(const string& prompt, int min = 0, int max = INT32_MAX) {
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


bool isValidName(const string& name) {
    if (name.empty()) return false;

    regex namePattern0(R"(^([A-Z]{1}[a-z]*)([- ][A-Z]{1}[a-z]*)*$)");
    regex namePattern1(R"(^([A-Z]{2}[a-z]*)([- ][A-Z]{2}[a-z]*)*$)");
    regex namePattern2(R"(^([A-Z]{2}[a-z]*)([- ][A-Z]{2}[a-z]*)*$)");
    regex namePattern3(R"(^([A-Z]{2}[a-z]*)([- ][A-Z]{2}[a-z]*)*$)");

    if (regex_match(name, namePattern0) || regex_match(name, namePattern1) || regex_match(name, namePattern2) || regex_match(name, namePattern2) )
        return true;
    return false;
}


string inputValidatedName(const string& prompt, bool canBeEmpty = false) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);

        if (name.empty() && canBeEmpty) return "EMPTY";

        if (isValidName(name)) return name;

        cout << "Invalid input!\n";
    }
}


bool isValidString(const string& str, const string& allowedChars, bool canBeEmpty) {
    if (canBeEmpty && str.empty()) return true;
    if (str.empty()) return false;

    bool hasAlpha = false;
    char c_prev = '\0';

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        if (isalpha(c)) {
            hasAlpha = true;
        }
        else if (allowedChars.find(c) == string::npos) {
            return false;
        }
        else if (c == c_prev) { 
            return false;
        }
        c_prev = c;
    }

    return hasAlpha;
}


string inputValidatedString(const string& prompt, const string& allowedChars, bool canBeEmpty, const string& strReplaced = "EMPTY") {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (isValidString(value, allowedChars, canBeEmpty)) {
            if (value.empty())
                return strReplaced;
            return value;
        }
        cout << "Invalid input!" << endl;
    }
}

double inputValidatedDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        // Исправление 1: Явное указание пространства имён для алгоритмов
        std::replace(input.begin(), input.end(), ',', '.');
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

        if (input.empty()) {
            cout << "Error: Empty input!\n";
            continue;
        }

        // Исправление 2: Используем std::count
        if (std::count(input.begin(), input.end(), '.') > 1) {
            cout << "Error: Multiple decimal points!\n";
            continue;
        }

        bool valid = true;
        bool digitFound = false;
        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (!isdigit(c) && c != '.' && !(i == 0 && (c == '-' || c == '+'))) {
                valid = false;
                break;
            }
            if (isdigit(c)) digitFound = true;
        }

        if (!valid || !digitFound) {
            cout << "Error: Invalid characters!\n";
            continue;
        }

        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            if (value >= min && value <= max) {
                return value;
            }
            cout << "Error: Value must be between " << min << " and " << max << "!\n";
        }
        else {
            cout << "Error: Invalid numeric format!\n";
        }
    }
}
