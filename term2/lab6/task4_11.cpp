#include <iostream>
#include "queue.h"
#include <sstream>
#include <cctype>  // For toupper and tolower functions

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

// Function to handle character input and transformation
void handleCharacterInput(Queue& queueLower, Queue& queueUpper) {
    char inputChar;
    cout << "Enter characters (enter '.' to finish):" << endl;
    while (true) {
        cin >> inputChar;
        if (inputChar == '.') {
            break;  // Stop input when a dot is entered
        }

        if (isupper(inputChar)) {
            // Convert to lowercase and add to the first queue
            inputChar = tolower(inputChar);
            char* lowerChar = new char(inputChar);
            if (!enQueue(queueLower, lowerChar)) {
                cout << "Queue 1 (lowercase) is full! Cannot add character: " << inputChar << endl;
                break;
            }
            cout << "Added to Queue 1 (lowercase): " << inputChar << endl;
        }
        else if (islower(inputChar)) {
            // Convert to uppercase and add to the second queue
            inputChar = toupper(inputChar);
            char* upperChar = new char(inputChar);
            if (!enQueue(queueUpper, upperChar)) {
                cout << "Queue 2 (uppercase) is full! Cannot add character: " << inputChar << endl;
                break;
            }
            cout << "Added to Queue 2 (uppercase): " << inputChar << endl;
        }
    }
}

// Function to display the contents of the queue
void displayQueue(const Queue& queue, int queueNum) {
    cout << "\nQueue " << queueNum << ": ";
    for (int i = queue.Head; i != queue.Tail; i = (i + 1) % queue.Size) {
        cout << *static_cast<char*>(queue.Data[i]) << " ";
    }
    cout << endl;
}

int main() {
    int maxSize = inputValidatedInt("Enter maximum queue size: ", 1, 100);

    // Create two queues for lowercase and uppercase characters
    Queue queueLower = createQueue(maxSize);
    Queue queueUpper = createQueue(maxSize);

    while (true) {
        cout << "\nQueue Menu\n"
            << "1. Enter characters\n"
            << "2. Show Queue 1 (lowercase)\n"
            << "3. Show Queue 2 (uppercase)\n"
            << "4. Clear queues\n"
            << "5. Exit\n"
            << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();  // To ignore the newline character after entering the number

        switch (choice) {
        case 1:
            handleCharacterInput(queueLower, queueUpper);
            break;

        case 2:
            displayQueue(queueLower, 1);
            break;

        case 3:
            displayQueue(queueUpper, 2);
            break;

        case 4:
            clearQueue(queueLower);
            clearQueue(queueUpper);
            cout << "Queues cleared." << endl;
            break;

        case 5:
            releaseQueue(queueLower);
            releaseQueue(queueUpper);
            cout << "Exiting the program." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
