#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include "validators.h"
using namespace std;


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

double inputValidatedDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        replace(input.begin(), input.end(), ',', '.');
        input.erase(remove(input.begin(), input.end(), ' '), input.end());

        if (input.empty()) {
            cout << "Error: Empty input!\n";
            continue;
        }

        if (count(input.begin(), input.end(), '.') > 1) {
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


string inputValidatedString(const string& prompt, const string& allowedChars, bool canBeEmpty, const string& strReplaced) {
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


bool isValidName(const string& name) {
    if (name.empty()) return false;
    regex namePattern(R"(^([A-Z][a-z]*)(-([A-Z][a-z]*))?( [a-z]*)*$)");

    return regex_match(name, namePattern);
}


string inputValidatedName(const string& prompt, bool canBeEmpty) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);

        if (name.empty() && canBeEmpty) return "EMPTY";

        if (isValidName(name)) return name;

        cout << "Invalid input!\n";
    }
}


string validateTime(const string& input) {
    string time = input;
    if (time.empty()) return "";

    if (time.size() == 4 && time[1] == ':') time = "0" + time;
    if (time.size() == 3 && time[0] == ':') time = "00" + time;
    if (time.size() == 1) time = "0" + time + ":00";

    if (time.size() != 5 || time[2] != ':' ||
        !isdigit(time[0]) || !isdigit(time[1]) ||
        !isdigit(time[3]) || !isdigit(time[4])) return "";

    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return "";

    return time;
}

string inputTime(const string& prompt) {
    string time;
    while (true) {
        cout << prompt;
        getline(cin, time);
        string formatted = validateTime(time);
        if (!formatted.empty()) return formatted;
        cout << "Invalid time! Examples: 04:06, 23:59, 12:00\n";
    }
}


bool isValidCountryOrTownName(const string& name) {
    regex pattern(R"(^[A-Z][a-z]+(-[A-Z][a-z]+){0,2}$)");
    return regex_match(name, pattern);

    if (regex_match(name, pattern))
        return true;

    return false;
}


string inputValidatedCountryOrTownName(const string& prompt, bool canBeEmpty) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);
        if (name == "" && canBeEmpty)
            return "EMPTY";
        if (isValidCountryOrTownName(name)) return name;

        cout << "Invalid input!\n";
    }
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
    regex phonePattern(R"(^\+375\s?\(?\d{2}\)?\s?\d{3}[- ]?\d{2}[- ]?\d{2}$)");

    return regex_match(phoneNumber, phonePattern);
}

string inputValidatedPhoneNumber(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);

        if (isValidPhoneNumber(name)) return name;

        cout << "Enter phone number (formats: +375 XX XXX XX XX, +375 XX XXX-XX-XX, +375 XX XXX XX-XX): ";
    }
}