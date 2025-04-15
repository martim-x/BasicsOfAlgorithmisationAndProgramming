#include <vector>
#include <string>

class CharHashTable {
    struct Node {
        char character;
        int count;
        Node* next;
        Node(char c) : character(c), count(1), next(nullptr) {}
    };

    std::vector<Node*> table;
    size_t capacity;

    size_t hash(char c) const {
        return static_cast<size_t>(c) % capacity;
    }

public:
    CharHashTable(size_t size);
    ~CharHashTable();

    void insert(char c);
    int search(char c) const;
    void display() const;
    void clear();
};