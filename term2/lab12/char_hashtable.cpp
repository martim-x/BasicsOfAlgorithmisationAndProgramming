#include "char_hashtable.h"
#include <iostream>

CharHashTable::CharHashTable(size_t size) : capacity(size) {
    table.resize(capacity, nullptr);
}

CharHashTable::~CharHashTable() {
    clear();
}

void CharHashTable::insert(char c) {
    size_t index = hash(c);
    Node* current = table[index];

    while (current) {
        if (current->character == c) {
            current->count++;
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(c);
    newNode->next = table[index];
    table[index] = newNode;
}

int CharHashTable::search(char c) const {
    size_t index = hash(c);
    Node* current = table[index];

    while (current) {
        if (current->character == c) {
            return current->count;
        }
        current = current->next;
    }
    return 0;
}

void CharHashTable::display() const {
    for (char c = 'A'; c <= 'Z'; ++c) {
        int count = search(c);
        if (count > 0) std::cout << c << ": " << count << "\n";
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        int count = search(c);
        if (count > 0) std::cout << c << ": " << count << "\n";
    }
}

void CharHashTable::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}