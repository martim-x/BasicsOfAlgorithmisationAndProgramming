#include "queue.h"
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

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

void shiftQueue(Queue& q, int maxIndex) {
    for (int i = 0; i < maxIndex; i++) {
        void* temp = delQueue(q);
        enQueue(q, temp);
    }
}

int main() {
    int n = inputValidatedInt("Enter the queue size: ", 1, 100);
    Queue q(n);
    float* elements = new float[n];

    for (int i = 0; i < n; i++) {
        elements[i] = inputValidatedDouble("Enter a floating-point number (-1000 to 1000): ", -1000, 1000);
        enQueue(q, &elements[i]);
    }

    cout << "Queue initialized successfully!" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Shift queue\n";
        cout << "2. Exit\n";
        cout << "Choose an option: ";

        int choice = inputValidatedInt("", 1, 3);

        switch (choice) {
        case 1: {
            int maxIndex = 0;
            float maxValue = *(float*)q.Data[q.Head];
            int index = q.Head;
            for (int i = 0; i < n; i++) {
                if (*(float*)q.Data[index] > maxValue) {
                    maxValue = *(float*)q.Data[index];
                    maxIndex = i;
                }
                index = (index + 1) % q.Size;
            }
            shiftQueue(q, maxIndex);
            cout << "Queue after shift:" << endl;
            for (int i = 0; i < n; i++) {
                cout << *(float*)q.Data[q.Head] << " ";
                enQueue(q, delQueue(q));
            }
            cout << endl;
            break;
        }
        case 2: {
            delete[] elements;
            releaseQueue(q);
            cout << "Exiting...\n";
            return 0;
        }
        }
    }

}

