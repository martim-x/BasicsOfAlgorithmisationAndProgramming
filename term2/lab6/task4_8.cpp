#include <iostream>
#include "queue.h"
#include <sstream>

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

void removeFirstNegative(Queue& q) {
    int size = q.Tail - q.Head;
    if (size < 0) size += q.Size;

    for (int i = 0; i < size; ++i) {
        int* element = static_cast<int*>(q.Data[q.Head]);
        if (*element < 0) {
            delQueue(q);
            cout << "First negative element removed: " << *element << endl;
            return;
        }
        q.Head = (q.Head + 1) % q.Size;
    }
    cout << "No negative elements found." << endl;
}

int main() {
    int maxSize = inputValidatedInt("Enter max size of queue: ", 1, 100);
    Queue q = createQueue(maxSize);

    while (true) {
        cout << "\nQueue Menu\n"
            << "1. Enqueue\n"
            << "2. Dequeue\n"
            << "3. Peek Front\n"
            << "4. Show Queue\n"
            << "5. Clear Queue\n"
            << "6. Remove First Negative Element\n"
            << "7. Exit\n"
            << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int value;
            value = inputValidatedInt("Enter value (-1000 - 1000): ", -1000, 1000);
            int* val = new int(value);
            if (enQueue(q, val)) {
                cout << "Enqueued: " << value << endl;
            }
            break;
        }

        case 2: {
            int* value = static_cast<int*>(delQueue(q));
            if (value) {
                cout << "Dequeued: " << *value << endl;
                delete value;
            }
            break;
        }

        case 3: {
            int* value = static_cast<int*>(peekQueue(q));
            if (value) {
                cout << "Front of queue: " << *value << endl;
            }
            break;
        }

        case 4:
            cout << "Queue: ";
            for (int i = q.Head; i != q.Tail; i = (i + 1) % q.Size) {
                cout << *static_cast<int*>(q.Data[i]) << " ";
            }
            cout << endl;
            break;

        case 5:
            clearQueue(q);
            cout << "Queue cleared." << endl;
            break;

        case 6:
            removeFirstNegative(q);
            break;

        case 7:
            releaseQueue(q);
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
