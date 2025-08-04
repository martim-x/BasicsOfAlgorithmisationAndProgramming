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

int HashTable::quadraticHash(const std::string& key, int i) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
    }
    return (hash + C1 * i + C2 * i * i) % capacity;
}

int HashTable::additiveHash(const std::string& key) const {
    int hash = 0;
    for (char c : key) {
        hash += c;
    }
    return hash % capacity;
}

int HashTable::openAddressHash(const std::string& key, int i) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
    }
    return (hash + i) % capacity;
}

int HashTable::universalHash(const std::string& key, int i) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * A + c + B) % capacity;
    }
    return (hash + i) % capacity;
}

void HashTable::countCollision(int originalHash, int currentHash, int i) {
    if (i > 0) {
        collisionCount++;
        std::cout << "Collision detected at index " << currentHash << " (original index: " << originalHash << ")" << std::endl;
    }
}

void HashTable::rehash() {
    int newCapacity = capacity * 2;
    std::vector<HashNode> newTable(newCapacity);
    collisionCount = 0;
    
    for (int i = 0; i < capacity; i++) {
        if (!table[i].isEmpty && !table[i].isDeleted) {
            std::string key = table[i].key;
            std::string value = table[i].value;
            
            int j = 0;
            int index;
            int originalHash;
            
            do {
                switch (hashType) {
                    case HashType::QUADRATIC:
                        originalHash = quadraticHash(key, 0);
                        index = quadraticHash(key, j);
                        break;
                    case HashType::ADDITIVE:
                        originalHash = additiveHash(key);
                        index = (originalHash + j) % newCapacity;
                        break;
                    case HashType::OPEN_ADDRESS:
                        originalHash = openAddressHash(key, 0);
                        index = openAddressHash(key, j);
                        break;
                    case HashType::UNIVERSAL:
                        originalHash = universalHash(key, 0);
                        index = universalHash(key, j);
                        break;
                }
                
                countCollision(originalHash, index, j);
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

void HashTable::insert(const std::string& key, const std::string& value) {
    int i = 0;
    int index;
    int originalHash;
    std::vector<bool> visited(capacity, false);
    
    do {
        switch (hashType) {
            case HashType::QUADRATIC:
                originalHash = quadraticHash(key, 0);
                index = quadraticHash(key, i);
                break;
            case HashType::ADDITIVE:
                originalHash = additiveHash(key);
                index = (originalHash + i) % capacity;
                break;
            case HashType::OPEN_ADDRESS:
                originalHash = openAddressHash(key, 0);
                index = openAddressHash(key, i);
                break;
            case HashType::UNIVERSAL:
                originalHash = universalHash(key, 0);
                index = universalHash(key, i);
                break;
        }
        
        if (visited[index]) {
            rehash();
            i = 0;
            visited.assign(capacity, false);
            continue;
        }
        
        visited[index] = true;
        countCollision(originalHash, index, i);
        i++;
    } while (!table[index].isEmpty && !table[index].isDeleted);
    
    table[index].key = key;
    table[index].value = value;
    table[index].isEmpty = false;
    table[index].isDeleted = false;
    size++;
    loadFactor = static_cast<double>(size) / capacity;
}

void HashTable::remove(const std::string& key) {
    int i = 0;
    int index;
    std::vector<bool> visited(capacity, false);
    
    do {
        switch (hashType) {
            case HashType::QUADRATIC:
                index = quadraticHash(key, i);
                break;
            case HashType::ADDITIVE:
                index = (additiveHash(key) + i) % capacity;
                break;
            case HashType::OPEN_ADDRESS:
                index = openAddressHash(key, i);
                break;
            case HashType::UNIVERSAL:
                index = (universalHash(key, 0) + i) % capacity;
                break;
        }
        
        if (visited[index]) {
            return;
        }
        
        visited[index] = true;
        i++;
    } while (!table[index].isEmpty && table[index].key != key);
    
    if (!table[index].isEmpty && table[index].key == key) {
        table[index].isDeleted = true;
        size--;
        loadFactor = static_cast<double>(size) / capacity;
    }
}

std::string HashTable::search(const std::string& key) {
    int i = 0;
    int index;
    std::vector<bool> visited(capacity, false);
    
    do {
        switch (hashType) {
            case HashType::QUADRATIC:
                index = quadraticHash(key, i);
                break;
            case HashType::ADDITIVE:
                index = (additiveHash(key) + i) % capacity;
                break;
            case HashType::OPEN_ADDRESS:
                index = openAddressHash(key, i);
                break;
            case HashType::UNIVERSAL:
                index = (universalHash(key, 0) + i) % capacity;
                break;
        }
        
        if (visited[index]) {
            return "";
        }
        
        visited[index] = true;
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
    std::cout << "Collisions: " << collisionCount << std::endl;
}

void HashTable::clear() {
    table.clear();
    size = 0;
    loadFactor = 0.0;
    table.resize(capacity);
}

void HashTable::measureSearchTime(const std::string& key) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::string result = search(key);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Search for key " << key << ": ";
    if (!result.empty()) {
        std::cout << "Found, time: " << duration.count() << " milliseconds" << std::endl;
    } else {
        std::cout << "Not found, time: " << duration.count() << " milliseconds" << std::endl;
    }
} 