#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <chrono>

enum class HashType {
    LINEAR,
    QUADRATIC,
    DOUBLE,
    UNIVERSAL
};

struct HashNode {
    int key;
    std::string value;
    bool isDeleted;
    bool isEmpty;

    HashNode() : key(0), value(""), isDeleted(false), isEmpty(true) {}
};

class HashTable {
private:
    std::vector<HashNode> table;
    int size;
    int capacity;
    double loadFactor;
    HashType hashType;
    
    // Константы для квадратичного зондирования
    const int C1 = 1;
    const int C2 = 1;
    
    // Константы для универсального хеширования
    const int A = 2654435761; // Золотое сечение
    const int B = 0;
    
    int hashFunction(int key) const;
    int linearProbe(int key, int i) const;
    int quadraticProbe(int key, int i) const;
    int doubleHash(int key, int i) const;
    int universalHash(int key, int i) const;
    void rehash();

public:
    HashTable(int initialSize, HashType type = HashType::LINEAR);
    ~HashTable();
    
    void insert(int key, const std::string& value);
    void remove(int key);
    std::string search(int key);
    void display() const;
    void displayStats() const;
    void clear();
    void measureSearchTime(int key);
};

#endif 