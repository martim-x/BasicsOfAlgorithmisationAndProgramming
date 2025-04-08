#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <chrono>

enum class HashType {
    QUADRATIC,    // Вариант 1: Квадратичное пробирование
    ADDITIVE,     // Вариант 8: Аддитивный метод
    OPEN_ADDRESS, // Вариант 11: Открытая адресация
    UNIVERSAL     // Вариант 14: Универсальное хеширование
};

struct HashNode {
    std::string key;
    std::string value;
    bool isDeleted;
    bool isEmpty;

    HashNode() : key(""), value(""), isDeleted(false), isEmpty(true) {}
};

class HashTable {
private:
    std::vector<HashNode> table;
    int size;
    int capacity;
    double loadFactor;
    HashType hashType;
    int collisionCount = 0;
    
    // Константы для квадратичного пробирования
    const int C1 = 1;
    const int C2 = 1;
    
    // Константы для универсального хеширования
    const int A = 4;  // Уменьшаем константу A
    const int B = 3;
    
    // Базовые функции хеширования
    int quadraticHash(const std::string& key, int i) const;
    int additiveHash(const std::string& key) const;
    int openAddressHash(const std::string& key, int i) const;
    int universalHash(const std::string& key, int i) const;
    
    void rehash();
    void countCollision(int originalHash, int currentHash, int i);

public:
    HashTable(int initialSize, HashType type = HashType::QUADRATIC);
    ~HashTable();
    
    void insert(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    std::string search(const std::string& key);
    void display() const;
    void displayStats() const;
    void clear();
    void measureSearchTime(const std::string& key);
    
    // Методы для доступа к элементам таблицы
    int getCapacity() const { return capacity; }
    int getSize() const { return size; }
    bool isEmpty(int index) const { return table[index].isEmpty; }
    bool isDeleted(int index) const { return table[index].isDeleted; }
    std::string getKey(int index) const { return table[index].key; }
    std::string getValue(int index) const { return table[index].value; }
};

#endif 