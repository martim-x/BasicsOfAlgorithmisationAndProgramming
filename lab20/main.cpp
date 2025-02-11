#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using
std::endl,
std::cout,
std::cin,
std::ifstream,
std::ofstream,
std::vector,
std::map;


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
        mapLetters[element, 0];


    for (auto element : vecVowels)
        mapLetters[element, 1];

    int count = 0;
    int line = 0;

    char symbol;
    while (inputFile >> symbol) {
        if (mapLetters.find(symbol) != mapLetters.end())
            count += mapLetters[symbol];

        if (symbol == '\n') {
            vecCountIndexed.push_back(count);
            count = 0;
        }
    }
    inputFile.close();
    for (int i = 0; i < vecCountIndexed.size(); i++)
        if (count <= vecConstenants[i]) {
            count = vecConstenants[i];
            line = i;
        }

    cout << count << endl;
    ifstream inputFile2("resource/input8_1.txt");
    ofstream outputFile("resource/output8_1.txt");
    while (inputFile2 >> symbol) {
        if (symbol == '\n')
            line++;
        if (line != count)
            outputFile << symbol;
    }
    inputFile2.close();
}


int main() {
    task8_1();
    return 0;
}