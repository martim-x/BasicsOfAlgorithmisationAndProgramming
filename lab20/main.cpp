#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void task8_1() {
    ifstream inputFile("resource/input8_1.txt");
    map<char, int> mapLetters;
    vector<char> vecVowels = { 'a', 'e', 'i', 'o', 'u' };
    vector<char> vecConstenants = { 'b', 'c', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', 'm',
        'n', 'p', 'q', 'r', 's',
        't', 'v', 'w', 'x', 'y', 'z' };

    vector<int> vecCountIndexed;

    for (auto element : vecConstenants)
        mapLetters[element] = 0;

    for (auto element : vecVowels)
        mapLetters[element] = 1;

    int count = 0;
    int line = -1;

    char symbol;
    while (inputFile.get(symbol)) {
        if (mapLetters.find(symbol) != mapLetters.end())
            count += mapLetters[symbol];

        if (symbol == '\n') {
            cout << count << endl;
            vecCountIndexed.push_back(count);
            count = 0;
        }
    }
    inputFile.close();

    for (int i = 0; i < vecCountIndexed.size(); i++)
        if (count < vecCountIndexed[i]) {
            count = vecCountIndexed[i];
            line = i;
        }


    ifstream inputFile2("resource/input8_1.txt");
    ofstream outputFile("resource/output8_1.txt");
    int currentLine = 0;

    while (inputFile2.get(symbol)) {
        if (symbol == '\n')
            currentLine++;

        if (currentLine != line)
            outputFile << symbol;
    }

    if (line != -1)
        outputFile << '\n' << ++line;

    inputFile2.close();
    outputFile.close();
}


void task8_2() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '.') {
            if (i > 0 && i < input.length() - 1 && isdigit(input[i - 1]) && isdigit(input[i + 1])) {
                int startApex = i - 1;
                while (startApex > 0 && isdigit(input[startApex - 1])) startApex--;
                if (startApex > 0 && (input[startApex - 1] == '+' || input[startApex - 1] == '-')) startApex--;

                int end = i + 1;
                while (end < input.length() && isdigit(input[end])) end++;

                cout << "Найденное вещественное число: " << input.substr(startApex, end - startApex) << endl;
                return;
            }
        }
    }

    cout << "Вещественное число не найдено." << endl;
}

int main() {
    task8_1();
    task8_2();
    return 0;
}
