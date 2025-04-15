#include "chainhashtable.h"
#include <iostream>

ChainHashTable::ChainHashTable(size_t initialCapacity)
    : capacity(initialCapacity) {
    table.resize(capacity, nullptr);
}

ChainHashTable::~ChainHashTable() {
    clear();
}

void ChainHashTable::insert(int flightNumber, const std::string& destination) {
    size_t index = universalHash(flightNumber);
    Flight* newFlight = new Flight(flightNumber, destination);

    if (!table[index]) {
        table[index] = newFlight;
    }
    else {
        Flight* current = table[index];
        while (current->next) {
            current = current->next;
        }
        current->next = newFlight;
    }
}

bool ChainHashTable::remove(int flightNumber) {
    size_t index = universalHash(flightNumber);
    Flight* current = table[index];
    Flight* prev = nullptr;

    while (current) {
        if (current->number == flightNumber) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                table[index] = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

std::string ChainHashTable::search(int flightNumber) {
    size_t index = universalHash(flightNumber);
    Flight* current = table[index];

    while (current) {
        if (current->number == flightNumber) {
            return current->destination;
        }
        current = current->next;
    }
    return "";
}

void ChainHashTable::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        std::cout << "Bucket " << i << ":\n";
        Flight* current = table[i];
        while (current) {
            std::cout << "  Flight " << current->number
                << " -> " << current->destination << "\n";
            current = current->next;
        }
    }
}

void ChainHashTable::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        Flight* current = table[i];
        while (current) {
            Flight* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}