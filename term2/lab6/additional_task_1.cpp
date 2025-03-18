#include <iostream>
#include <sstream>

using namespace std;

struct Item {
    int data;
    Item* next;
    Item* prev;
};

Item* minLifoHead = nullptr, * minLifoTail = nullptr;
Item* maxFifoHead = nullptr, * maxFifoTail = nullptr;
Item* minLifoEndHead = nullptr, * minLifoEndTail = nullptr;
Item* maxFifoEndHead = nullptr, * maxFifoEndTail = nullptr;


void deleteFirst(Item*& head, Item*& tail) {
    if (!head) return;
    Item* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
}


void deleteLast(Item*& head, Item*& tail) {
    if (!tail) return;
    Item* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete temp;
}


void insertMinLIFO(int x, Item*& head, Item*& tail) {
    Item* newItem = new Item{ x, nullptr, nullptr };

    if (!head || x <= head->data) {
        newItem->next = head;
        if (head) head->prev = newItem;
        head = newItem;
        if (!tail) tail = head;
        return;
    }

    Item* curr = head;
    while (curr->next && curr->next->data < x)
        curr = curr->next;

    newItem->next = curr->next;
    newItem->prev = curr;
    if (curr->next) curr->next->prev = newItem;
    curr->next = newItem;

    if (!newItem->next) tail = newItem;
}


void insertMaxFIFO(int x, Item*& head, Item*& tail) {
    Item* newItem = new Item{ x, nullptr, nullptr };

    if (!head || x >= head->data) {
        newItem->next = head;
        if (head) head->prev = newItem;
        head = newItem;
        if (!tail) tail = head;
        return;
    }

    Item* curr = head;
    while (curr->next && curr->next->data > x)
        curr = curr->next;

    newItem->next = curr->next;
    newItem->prev = curr;
    if (curr->next) curr->next->prev = newItem;
    curr->next = newItem;

    if (!newItem->next) tail = newItem;
}


void printQueue(Item* head) {
    if (!head) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "Queue: ";
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}


int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) return value;
        cout << "Invalid input! Please try again.\n";
    }
}


int main() {
    int queueType = 0;
    while (true) {
        cout << "\nSelect Queue Type:\n"
            "1 - Min Priority LIFO (delete from head)\n"
            "2 - Max Priority FIFO (delete from head)\n"
            "3 - Min Priority LIFO (delete from tail)\n"
            "4 - Max Priority FIFO (delete from tail)\n"
            "0 - Exit\n";

        queueType = inputValidatedInt("Choice (0-4): ", 0, 4);
        if (queueType == 0) break;

        while (true) {
            cout << "\nOperations for selected queue:\n"
                "1 - Insert\n"
                "2 - Delete\n"
                "3 - Print\n"
                "4 - Back to queue type selection\n";

            int op = inputValidatedInt("Choice (1-4): ", 1, 4);
            if (op == 4) break;

            switch (op) {
            case 1: {
                int val = inputValidatedInt("Enter value (-1000-1000): ", -1000, 1000);
                switch (queueType) {
                case 1: insertMinLIFO(val, minLifoHead, minLifoTail); break;
                case 2: insertMaxFIFO(val, maxFifoHead, maxFifoTail); break;
                case 3: insertMinLIFO(val, minLifoEndHead, minLifoEndTail); break;
                case 4: insertMaxFIFO(val, maxFifoEndHead, maxFifoEndTail); break;
                }
                break;
            }
            case 2: {
                switch (queueType) {
                case 1: deleteFirst(minLifoHead, minLifoTail); break;
                case 2: deleteFirst(maxFifoHead, maxFifoTail); break;
                case 3: deleteLast(minLifoEndHead, minLifoEndTail); break;
                case 4: deleteLast(maxFifoEndHead, maxFifoEndTail); break;
                }
                break;
            }
            case 3: {
                cout << "Selected queue: ";
                switch (queueType) {
                case 1: printQueue(minLifoHead); break;
                case 2: printQueue(maxFifoHead); break;
                case 3: printQueue(minLifoEndHead); break;
                case 4: printQueue(maxFifoEndHead); break;
                }
                break;
            }
            }
        }
    }
    return 0;
}

// Min Priority LIFO (удаление из головы):
// Сортировка по возрастанию.
// LIFO при одинаковых значениях.
// Удаление из головы.

// Max Priority FIFO (удаление из головы):
// Сортировка по убыванию.
// FIFO при одинаковых значенях.
// Удаление из головы.

// Min Priority LIFO (удаление из хвоста):
// Сортировка по возрастанию.
// LIFO при одинаковых значениях.
// Удаление из хвоста.

// Max Priority FIFO (удаление из хвоста):
// Сортировка по убыванию.
// FIFO при одинаковых значениях.
// Удаление из хвоста.