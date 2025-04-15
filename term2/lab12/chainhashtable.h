#include <vector>
#include <string>
#include <functional>

class ChainHashTable {
    struct Flight {
        int number;
        std::string destination;
        Flight* next;
        Flight(int num, const std::string& dest)
            : number(num), destination(dest), next(nullptr) {
        }
    };

    std::vector<Flight*> table;
    size_t capacity;
    const size_t A = 65537; // Large prime number
    const size_t B = 0;

    size_t universalHash(int key) const {
        return (A * key + B) % capacity;
    }

public:
    ChainHashTable(size_t initialCapacity);
    ~ChainHashTable();

    void insert(int flightNumber, const std::string& destination);
    bool remove(int flightNumber);
    std::string search(int flightNumber);
    void display() const;
    void clear();
};