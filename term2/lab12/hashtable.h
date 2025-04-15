#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>

class HashTable {
private:
    size_t table_size;
    std::vector<std::list<int>> buckets;

    size_t hash(int key) const {
        return (key * 2654435761U) % table_size; 
    }

public:
    explicit HashTable(size_t size = 101);
    void insert(int key);
    std::pair<bool, size_t> search(int key) const;
    void loadFromFile(const std::string& filename);
};

#endif