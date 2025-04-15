#include "hashtable.h"
#include <fstream>

HashTable::HashTable(size_t size)
    : table_size(size), buckets(size) {
}

void HashTable::insert(int key) {
    size_t index = hash(key);
    buckets[index].push_back(key);
}

std::pair<bool, size_t> HashTable::search(int key) const {
    size_t index = hash(key);
    size_t comparisons = 0;

    for (const auto& num : buckets[index]) {
        comparisons++;
        if (num == key) return { true, comparisons };
    }
    return { false, comparisons };
}

void HashTable::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("File not found: " + filename);

    int num;
    while (file >> num) insert(num);
}