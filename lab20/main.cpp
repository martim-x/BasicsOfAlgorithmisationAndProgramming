#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;


void task1_1() {
    cout << "*** TASK1~1 ***" << endl << endl;
    ifstream inputFile("resource/input1_1.txt");
    ofstream outputFile("resource/output1_1.txt");

    string inputLine;
    int counter = 1;

    while (getline(inputFile, inputLine)) {
        if (counter % 2 == 0)
            outputFile << inputLine << endl;
        counter++;
    }

    inputFile.close();
    outputFile.close();

    ifstream file1("resource/input1_1.txt", ios::binary | ios::ate);
    ifstream file2("resource/output1_1.txt", ios::binary | ios::ate);

    cout << "Size of input1_1.txt: " << file1.tellg() << "bytes" << endl;
    cout << "Size of output1_1.txt: " << file2.tellg() << " bytes" << endl;
}


void task1_2() {
    cout << "*** TASK1~2 ***" << endl << endl;
    ofstream outputFile("resource/output1_2.txt");
    ofstream inputFile("resource/input1_2.txt");

    string inputLine;
    cout << "Input string of number and letters devided by spaces: ";
    getline(cin, inputLine);

    inputFile << inputLine;
    inputFile.close();

    ifstream inputFileRead("resource/input1_2.txt");

    string word;
    inputLine = "";
    int counter = 0;
    getline(inputFileRead, inputLine);

    stringstream stream(inputLine);
    while (stream >> word) {
        bool isNumber = true;
        for (char c : word) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (isNumber && !word.empty()) {
            int number = stoi(word);
            if (number % 2 != 0) {
                outputFile << number << " ";
                counter++;
            }
        }
    }

    cout << "Was wrote " << counter << " odd numbers" << endl << endl;
    outputFile.close();
    inputFileRead.close();
}


void task8_1() {
    cout << "*** TASK8~1 ***" << endl << endl;

    ifstream inputFile("resource/input8_1.txt");

    map<char, int> mapLetters;
    vector<char> vecVowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
    vector<int> vecCountIndexed;
    string lineStr;


    for (char c : vecVowels) {
        mapLetters[c] = 1;
    }

    for (char c = 'a'; c <= 'z'; ++c) {
        if (mapLetters.find(c) == mapLetters.end()) {
            mapLetters[c] = 0;
        }
    }

    int lineCount = 0;
    int maxVowelsCount = 0;
    int lineWithMaxVowels = -1;

    while (getline(inputFile, lineStr)) {
        lineCount++;
        int vowelsCount = 0;

        for (char ch : lineStr) {
            if (mapLetters.find(ch) != mapLetters.end()) {
                vowelsCount += mapLetters[ch];
            }
        }


        if (vowelsCount > maxVowelsCount) {
            maxVowelsCount = vowelsCount;
            lineWithMaxVowels = lineCount;
        }

        vecCountIndexed.push_back(vowelsCount);
    }

    inputFile.close();

    if (lineWithMaxVowels != -1) {
        cout << "Line with the most vowels: " << lineWithMaxVowels << endl;
    }

    ifstream inputFileRead("resource/input8_1.txt");
    ofstream outputFile("resource/output8_1.txt");
    int currentLine = 0;

    while (getline(inputFileRead, lineStr)) {
        currentLine++;
        if (currentLine != lineWithMaxVowels) {
            outputFile << lineStr << endl;
        }
    }

    inputFileRead.close();
    outputFile.close();
}


void task8_2() {
    cout << "*** TASK8~2 ***" << endl << endl;
    string input;
    cout << "Input string: ";
    getline(cin, input);

    ofstream outputFile("resource/output8_2.txt");
    ofstream inputFile("resource/input8_2.txt");

    inputFile << input;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '.') {
            if (i > 0 && i < input.length() - 1 && isdigit(input[i - 1]) && isdigit(input[i + 1])) {
                int startApex = i - 1;
                while (startApex > 0 && isdigit(input[startApex - 1])) startApex--;
                if (startApex > 0 && (input[startApex - 1] == '+' || input[startApex - 1] == '-')) startApex--;

                int end = i + 1;
                while (end < input.length() && isdigit(input[end])) end++;

                outputFile << "Found real number: " << input.substr(startApex, end - startApex);
                return;
            }
        }
    }

    outputFile << "Did't find real number" << endl << endl;
}


void task11_1() {
    cout << "*** TASK11~1 ***" << endl << endl;

    ifstream inputFile("resource/input11_1.txt");
    ofstream outputFile("resource/output11_1.txt");

    string inputLine;
    int totalChars = 0;

    while (getline(inputFile, inputLine)) {
        istringstream stream(inputLine);
        string word;
        int wordCount = 0;

        while (stream >> word) {
            wordCount++;
        }

        if (wordCount == 1) {
            bool isValidWord = true;
            for (char c : inputLine) {
                if (!isalpha(c)) {
                    isValidWord = false;
                    break;
                }
            }

            if (isValidWord) {
                outputFile << inputLine << endl;
                totalChars += inputLine.length();
            }
        }
    }

    outputFile << "Total characters in FILE2: " << totalChars << endl;

    inputFile.close();
    outputFile.close();
}

void task11_2() {
    cout << "*** TASK11~2 ***" << endl << endl;

    ofstream inputFile("resource/input11_2.txt");

    string frstLine, scndLine;
    cout << "Input first string: ";
    getline(cin, frstLine);
    inputFile << frstLine << endl;

    cout << "Input second string: ";
    getline(cin, scndLine);
    inputFile << scndLine << endl;

    inputFile.close();

    ifstream inputFileRead("resource/input11_2.txt");

    getline(inputFileRead, frstLine);
    getline(inputFileRead, scndLine);
    inputFileRead.close();

    vector<string> wordsFrstLine, wordsScndLine;


    istringstream stream1(frstLine), stream2(scndLine);
    string word;

    while (stream1 >> word) {
        bool Validword = true;
        for (char c : word) {
            if (!isalpha(c)) {
                Validword = false;
                break;
            }
        }

        if (Validword)
            wordsFrstLine.push_back(word);
    }

    while (stream2 >> word) {
        bool Validword = true;
        for (char c : word) {
            if (!isalpha(c)) {
                Validword = false;
                break;
            }
        }

        if (Validword)
            wordsScndLine.push_back(word);
    }

    string minWord = wordsFrstLine.empty() ? "" : wordsFrstLine[0];
    for (const auto& w : wordsFrstLine) {
        if (w.length() < minWord.length()) {
            minWord = w;
        }
    }

    string maxWord = wordsScndLine.empty() ? "" : wordsScndLine[0];
    for (const auto& w : wordsScndLine) {
        if (w.length() > maxWord.length()) {
            maxWord = w;
        }
    }

    ofstream outputFile("resource/output11_2.txt");
    outputFile << "Shortest word in first line: " << minWord << endl;
    outputFile << "Longest word in second line: " << maxWord << endl;

    outputFile.close();
}



void task14_1() {
    cout << "*** TASK14~1 ***" << endl << endl;
    ifstream inputFile("resource/input14_1.txt");
    ofstream outputFile("resource/output14_1.txt");

    string inputLine;
    vector<string> words;

    int line = 0;
    int maxA;
    int maxWordIndex;

    while (getline(inputFile, inputLine)) {
        istringstream stream(inputLine);
        words.clear();

        string word;
        map<string, int> wordCount;

        while (stream >> word) {
            bool validWord = true;
            for (char c : word) {
                if (!isalpha(c)) {
                    validWord = false;
                    break;
                }
            }

            if (validWord) {
                words.push_back(word);
                wordCount[word]++;
            }
        }

        bool hasTwoSameWords = false;
        for (const auto& entry : wordCount) {
            if (entry.second == 2) {
                hasTwoSameWords = true;
                break;
            }
        }

        if (hasTwoSameWords) {
            outputFile << inputLine << endl;
            line++;

            maxA = 0;
            maxWordIndex = -1;

            for (int i = 0; i < words.size(); ++i) {
                int countA = 0;
                for (char c : words[i]) {
                    if (tolower(c) == 'a') {
                        countA++;
                    }
                }

                if (countA > maxA) {
                    maxA = countA;
                    maxWordIndex = i;
                }
            }
        }
    }
    if (maxWordIndex != -1)
        outputFile << "Word with the most 'a' is placed in " << line << " line " << ++maxWordIndex << " position." << endl;

}



void task14_2() {
    cout << "*** TASK14~2 ***" << endl << endl;

    ofstream inputFile("resource/input14_2.txt");
    string inputLine;

    cout << "Input string: ";
    getline(cin, inputLine);

    inputFile << inputLine;
    inputFile.close();


    ifstream outputFile("resource/input14_2.txt");
    string fileContent;

    getline(outputFile, fileContent);
    outputFile.close();


    int k;
    cout << "Enter the value of k (length of the first substring): ";
    cin >> k;

    if (k > fileContent.length()) {
        cout << "Error: k exceeds the length of the string!" << endl;
        return;
    }

    string firstSubstring = fileContent.substr(0, k);
    string secondSubstring = fileContent.substr(k);

    cout << "First substring: " << firstSubstring << endl;
    cout << "Second substring: " << secondSubstring << endl;
}


int main() {
    task1_1();
    task1_2();

    task8_1();
    task8_2();

    task11_1();
    task11_2();

    task14_1();
    task14_2();
    return 0;
}
