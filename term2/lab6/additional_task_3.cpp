#include "queue.h"
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

void processFile(const char* inputFile, const char* outputFile) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    string line;

    while (getline(fin, line)) {
        int len = line.length();
        Queue nonDigits = createQueue(len);
        Queue digits = createQueue(len);

        for (char c : line) {
            char* element = new char(c);
            if (isdigit(c)) {
                if (!enQueue(digits, element)) delete element;
            }
            else {
                if (!enQueue(nonDigits, element)) delete element;
            }
        }

        string newLine;

        while (!nonDigits.isEmpty()) {
            char* ch = static_cast<char*>(delQueue(nonDigits));
            newLine += *ch;
            delete ch;
        }


        while (!digits.isEmpty()) {
            char* ch = static_cast<char*>(delQueue(digits));
            newLine += *ch;
            delete ch;
        }

        fout << newLine << endl;

        releaseQueue(nonDigits);
        releaseQueue(digits);
    }

    fin.close();
    fout.close();
}

int main() {
    processFile("input_add_t_3.txt", "output_add_t_3.txt");
    return 0;
}