#include "hash_table.h"
#include <iostream>
#include <chrono>

HashTable::HashTable(int initialSize, HashType type) 
    : size(0), capacity(initialSize), loadFactor(0.0), hashType(type) {
    table.resize(capacity);
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(int key) const {
    return key % capacity;
}

int HashTable::linearProbe(int key, int i) const {
    return (hashFunction(key) + i) % capacity;
}

int HashTable::quadraticProbe(int key, int i) const {
    return (hashFunction(key) + C1 * i + C2 * i * i) % capacity;
}

int HashTable::doubleHash(int key, int i) const {
    int h1 = hashFunction(key);
    int h2 = 1 + (key % (capacity - 1));
    return (h1 + i * h2) % capacity;
}

int HashTable::universalHash(int key, int i) const {
    return ((A * key + B) % capacity + i) % capacity;
}

void HashTable::rehash() {
    int newCapacity = capacity * 2;
    std::vector<HashNode> newTable(newCapacity);
    
    for (int i = 0; i < capacity; i++) {
        if (!table[i].isEmpty && !table[i].isDeleted) {
            int key = table[i].key;
            std::string value = table[i].value;
            
            int j = 0;
            int index;
            do {
                switch (hashType) {
                    case HashType::LINEAR:
                        index = linearProbe(key, j);
                        break;
                    case HashType::QUADRATIC:
                        index = quadraticProbe(key, j);
                        break;
                    case HashType::DOUBLE:
                        index = doubleHash(key, j);
                        break;
                    case HashType::UNIVERSAL:
                        index = universalHash(key, j);
                        break;
                }
                j++;
            } while (!newTable[index].isEmpty);
            
            newTable[index].key = key;
            newTable[index].value = value;
            newTable[index].isEmpty = false;
            newTable[index].isDeleted = false;
        }
    }
    
    table = std::move(newTable);
    capacity = newCapacity;
    loadFactor = static_cast<double>(size) / capacity;
}

void HashTable::insert(int key, const std::string& value) {
    if (loadFactor >= 0.8) {
        rehash();
    }
    
    int i = 0;
    int index;
    do {
        switch (hashType) {
            case HashType::LINEAR:
                index = linearProbe(key, i);
                break;
            case HashType::QUADRATIC:
                index = quadraticProbe(key, i);
                break;
            case HashType::DOUBLE:
                index = doubleHash(key, i);
                break;
            case HashType::UNIVERSAL:
                index = universalHash(key, i);
                break;
        }
        i++;
    } while (!table[index].isEmpty && !table[index].isDeleted && table[index].key != key);
    
    if (table[index].isEmpty || table[index].isDeleted) {
        size++;
    }
    
    table[index].key = key;
    table[index].value = value;
    table[index].isEmpty = false;
    table[index].isDeleted = false;
    
    loadFactor = static_cast<double>(size) / capacity;
}

void HashTable::remove(int key) {
    int i = 0;
    int index;
    do {
        switch (hashType) {
            case HashType::LINEAR:
                index = linearProbe(key, i);
                break;
            case HashType::QUADRATIC:
                index = quadraticProbe(key, i);
                break;
            case HashType::DOUBLE:
                index = doubleHash(key, i);
                break;
            case HashType::UNIVERSAL:
                index = universalHash(key, i);
                break;
        }
        i++;
    } while (!table[index].isEmpty && table[index].key != key);
    
    if (!table[index].isEmpty && table[index].key == key) {
        table[index].isDeleted = true;
        size--;
        loadFactor = static_cast<double>(size) / capacity;
    }
}

std::string HashTable::search(int key) {
    int i = 0;
    int index;
    do {
        switch (hashType) {
            case HashType::LINEAR:
                index = linearProbe(key, i);
                break;
            case HashType::QUADRATIC:
                index = quadraticProbe(key, i);
                break;
            case HashType::DOUBLE:
                index = doubleHash(key, i);
                break;
            case HashType::UNIVERSAL:
                index = universalHash(key, i);
                break;
        }
        i++;
    } while (!table[index].isEmpty && table[index].key != key);
    
    if (!table[index].isEmpty && !table[index].isDeleted && table[index].key == key) {
        return table[index].value;
    }
    return "";
}

void HashTable::display() const {
    for (int i = 0; i < capacity; i++) {
        if (!table[i].isEmpty && !table[i].isDeleted) {
            std::cout << "Index " << i << ": Key = " << table[i].key 
                      << ", Value = " << table[i].value << std::endl;
        }
    }
}

void HashTable::displayStats() const {
    std::cout << "Size: " << size << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Load Factor: " << loadFactor << std::endl;
}

void HashTable::clear() {
    table.clear();
    size = 0;
    loadFactor = 0.0;
    table.resize(capacity);
}

void HashTable::measureSearchTime(int key) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = search(key);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Search for key " << key << ": ";
    if (!result.empty()) {
        std::cout << "Found value '" << result << "'";
    } else {
        std::cout << "Not found";
    }
    std::cout << " in " << duration.count() << " nanoseconds" << std::endl;
} 