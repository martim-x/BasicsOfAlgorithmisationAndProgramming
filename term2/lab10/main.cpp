#include "binary_heap.h"
#include <iostream>
#include <string>
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

CompareResult compareInts(void* a, void* b) {
    int* intA = static_cast<int*>(a);
    int* intB = static_cast<int*>(b);
    if (*intA < *intB) return LESS;
    if (*intA > *intB) return GREATER;
    return EQUAL;
}

void showHeap(const Heap& heap) {
    if (heap.isEmpty()) {
        cout << "Heap is empty." << endl;
        return;
    }
    heap.display();
}

void showCurrentHeapInfo(const Heap* currentHeap, const Heap& heap1, const Heap& heap2) {
    cout << "\nCurrent heap: " << (currentHeap == &heap1 ? "Heap 1" : "Heap 2") << endl;
    cout << "Heap 1 size: " << heap1.currentSize << endl;
    cout << "Heap 2 size: " << heap2.currentSize << endl;
}

int menu() {
    cout << "\nBinary Heap Menu:\n"
        << "1. Select heap (1 or 2)\n"
        << "2. Create heap\n"
        << "3. Add element\n"
        << "4. Extract maximum element\n"
        << "5. Extract minimum element\n"
        << "6. Extract element by index\n"
        << "7. Show heap\n"
        << "8. Clear heap\n"
        << "9. Merge heaps\n"
        << "10. Exit\n";
    return inputValidatedInt("Enter your choice: ", 1, 10);
}

int main() {
    Heap heap1 = createHeap(0, compareInts);
    Heap heap2 = createHeap(0, compareInts);
    Heap* currentHeap = &heap1;
    bool heap1Created = false;
    bool heap2Created = false;

    while (true) {
        showCurrentHeapInfo(currentHeap, heap1, heap2);
        int choice = menu();

        switch (choice) {
        case 1: {
            int heapChoice = inputValidatedInt("Select heap (1 or 2): ", 1, 2);
            currentHeap = (heapChoice == 1) ? &heap1 : &heap2;
            cout << "Switched to Heap " << heapChoice << endl;
            break;
        }
        case 2: {
            int capacity = inputValidatedInt("Enter heap size (1-100): ", 1, 100);
            if (currentHeap == &heap1) {
                heap1 = createHeap(capacity, compareInts);
                heap1Created = true;
            }
            else {
                heap2 = createHeap(capacity, compareInts);
                heap2Created = true;
            }
            cout << "Heap created successfully." << endl;
            break;
        }
        case 3: {
            if (!heap1Created && currentHeap == &heap1) {
                cout << "Please create a heap first!" << endl;
                break;
            }
            if (!heap2Created && currentHeap == &heap2) {
                cout << "Please create a heap first!" << endl;
                break;
            }
            int value = inputValidatedInt("Enter value (-1000 - 1000): ", -1000, 1000);
            int* val = new int(value);
            currentHeap->insert(val);
            cout << "Element added successfully." << endl;
            break;
        }
        case 4: {
            if (currentHeap->isEmpty()) {
                cout << "Heap is empty!" << endl;
                break;
            }
            int* max = static_cast<int*>(currentHeap->extractMax());
            cout << "Extracted maximum element: " << *max << endl;
            delete max;
            break;
        }
        case 5: {
            if (currentHeap->isEmpty()) {
                cout << "Heap is empty!" << endl;
                break;
            }
            int* min = static_cast<int*>(currentHeap->extractMin());
            cout << "Extracted minimum element: " << *min << endl;
            delete min;
            break;
        }
        case 6: {
            if (currentHeap->isEmpty()) {
                cout << "Heap is empty!" << endl;
                break;
            }
            int index = inputValidatedInt("Enter element index: ", 0, currentHeap->currentSize - 1);
            int* elem = static_cast<int*>(currentHeap->extractByIndex(index));
            if (elem) {
                cout << "Extracted element: " << *elem << endl;
                delete elem;
            }
            break;
        }
        case 7: {
            showHeap(*currentHeap);
            break;
        }
        case 8: {
            currentHeap->currentSize = 0;
            cout << "Heap cleared successfully." << endl;
            break;
        }
        case 9: {
            if (!heap1Created || !heap2Created) {
                cout << "Both heaps must be created first!" << endl;
                break;
            }
            Heap mergedHeap = mergeHeaps(heap1, heap2);
            cout << "Merged heap:" << endl;
            showHeap(mergedHeap);
            break;
        }
        case 10: {
            while (!heap1.isEmpty()) {
                delete static_cast<int*>(heap1.extractMax());
            }
            while (!heap2.isEmpty()) {
                delete static_cast<int*>(heap2.extractMax());
            }
            return 0;
        }
        }
    }
}
