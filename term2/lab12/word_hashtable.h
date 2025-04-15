#include <vector>
#include <string>
#include <list>

class WordHashTable {
    struct WordGroup {
        char first_char;
        std::list<std::string> words;
        WordGroup* next;
        WordGroup(char c) : first_char(c), next(nullptr) {}
    };

    std::vector<WordGroup*> table;
    size_t capacity;

    size_t hash(char c) const {
        return static_cast<size_t>(c) % capacity;
    }

public:
    WordHashTable(size_t size);
    ~WordHashTable();

    void insert(const std::string& word);
    bool remove(char first_char);
    std::pair<int, bool> search(const std::string& word) const;
    void display() const;
    void saveToFile(const std::string& filename) const;
    void clear();
};