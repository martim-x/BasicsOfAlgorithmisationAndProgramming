#include <string>
#include <functional>
#include "validators.h"
using namespace std;

struct Person {
    string name;
    string phoneNumber;
    int age;
};

struct Element {
    Element* Prev;
    Element* Next;
    Person* Data;

    Element(Element* prev, Person* data, Element* next)
        : Prev(prev), Data(data), Next(next) {
    }
};

class List {
private:
    Element* Head;
    Element* Tail;

public:
    List() : Head(nullptr), Tail(nullptr) {}
    ~List();

    bool Insert(Person* data);      // Insert at the beginning
    bool InsertEnd(Person* data);   // Insert at the end
    Element* Search(const std::string& name); // Search by name
    bool Delete(const std::string& name);     // Delete by name
    void PrintList(std::function<void(Person*)> printFunc); // Print the list
    int CountList();                // Count elements
    bool DeleteList();              // Clear the list
};