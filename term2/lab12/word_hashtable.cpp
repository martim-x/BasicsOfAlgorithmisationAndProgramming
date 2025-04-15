#include "word_hashtable.h"
#include <fstream>
#include <iostream>
#include <algorithm>

WordHashTable::WordHashTable(size_t size) : capacity(size) {
    table.resize(capacity, nullptr);
}

WordHashTable::~WordHashTable() {
    clear();
}

void WordHashTable::insert(const std::string& word) {
    if (word.empty()) return;
    char first = word[0];
    size_t index = hash(first);

    WordGroup* current = table[index];
    while (current) {
        if (current->first_char == first) {
            current->words.push_back(word);
            return;
        }
        current = current->next;
    }

    WordGroup* newGroup = new WordGroup(first);
    newGroup->words.push_back(word);
    newGroup->next = table[index];
    table[index] = newGroup;
}

std::pair<int, bool> WordHashTable::search(const std::string& word) const {
    if (word.empty()) return { 0, false };
    char first = word[0];
    size_t index = hash(first);
    int comparisons = 0;

    WordGroup* group = table[index];
    while (group) {
        if (group->first_char == first) {
            for (const auto& w : group->words) {
                comparisons++;
                if (w == word) return { comparisons, true };
            }
            return { comparisons, false };
        }
        group = group->next;
        comparisons++;
    }
    return { comparisons, false };
}

bool WordHashTable::remove(char first_char) {
    size_t index = hash(first_char);
    WordGroup* prev = nullptr;
    WordGroup* current = table[index];

    while (current) {
        if (current->first_char == first_char) {
            if (prev) prev->next = current->next;
            else table[index] = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void WordHashTable::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        WordGroup* group = table[i];
        while (group) {
            std::cout << "[" << group->first_char << "]: ";
            for (const auto& w : group->words) {
                std::cout << w << " ";
            }
            std::cout << "\n";
            group = group->next;
        }
    }
}

void WordHashTable::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (size_t i = 0; i < capacity; ++i) {
        WordGroup* group = table[i];
        while (group) {
            file << "[" << group->first_char << "]: ";
            for (const auto& w : group->words) {
                file << w << " ";
            }
            file << "\n";
            group = group->next;
        }
    }
}

void WordHashTable::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        WordGroup* current = table[i];
        while (current) {
            WordGroup* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}