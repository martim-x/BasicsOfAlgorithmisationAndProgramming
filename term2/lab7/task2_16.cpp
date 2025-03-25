#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include "validators.h"

using namespace std;

const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address {
    string name;
    string city;
    Address* next;
    Address* prev;

    Address(const string& n, const string& c) : name(n), city(c), next(nullptr), prev(nullptr) {}
};

struct ListManager {
    Address* head = nullptr;
    Address* tail = nullptr;

    void clear() {
        while (head) {
            Address* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

enum CurrentList { LIST1, LIST2, RESULT };
CurrentList current = LIST1;
ListManager lists[3];

int getValidatedChoice() {
    return inputValidatedInt("Your choice: ", 0, 9);
}

void showListSelection() {
    cout << "\nCurrent list: ";
    switch (current) {
    case LIST1: cout << "List 1"; break;
    case LIST2: cout << "List 2"; break;
    case RESULT: cout << "Result"; break;
    }
    cout << endl;
}

int menu() {
    system("cls");
    showListSelection();
    cout << "\n1. Select list 1\n"
        << "2. Select list 2\n"
        << "3. Select result list\n"
        << "4. Add element\n"
        << "5. Remove element\n"
        << "6. Show list\n"
        << "7. Save to file\n"
        << "8. Load from file\n"
        << "9. CountX\n"
        << "0. Exit\n";
    return getValidatedChoice();
}

void insert(ListManager& manager, Address* e) {
    if (!manager.head) {
        manager.head = manager.tail = e;
        return;
    }
    manager.tail->next = e;
    e->prev = manager.tail;
    manager.tail = e;
}

Address* setElement() {
    string name = inputValidatedName("Enter name: ", false);
    string city = inputValidatedCountryOrTownName("Enter city: ");
    return new Address(name, city);
}

void deleteElement(ListManager& manager, const string& name) {
    Address* t = manager.head;
    while (t) {
        if (t->name == name) {
            if (t->prev) t->prev->next = t->next;
            else manager.head = t->next;

            if (t->next) t->next->prev = t->prev;
            else manager.tail = t->prev;

            delete t;
            cout << "Element deleted\n";
            return;
        }
        t = t->next;
    }
    cout << "Element not found\n";
}

void saveToFile(const ListManager& manager, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) throw runtime_error("Can't open file");

    // Записываем количество элементов
    int count = 0;
    Address* t = manager.head;
    while (t && ++count) t = t->next;
    fout.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Записываем данные
    t = manager.head;
    while (t) {
        fout.write(t->name.c_str(), NAME_SIZE);
        fout.write(t->city.c_str(), CITY_SIZE);
        t = t->next;
    }
}

void loadFromFile(ListManager& manager, const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) throw runtime_error("Can't open file");

    // Читаем количество элементов
    int count;
    fin.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (count < 0) throw runtime_error("Corrupted file");

    // Очищаем текущий список
    manager.clear();

    // Читаем элементы
    for (int i = 0; i < count; ++i) {
        char name[NAME_SIZE], city[CITY_SIZE];
        fin.read(name, NAME_SIZE);
        fin.read(city, CITY_SIZE);

        if (!isValidName(name) || !isValidCountryOrTownName(city))
            throw runtime_error("Corrupted data in file");

        insert(manager, new Address(name, city));
    }
}

int countX(const ListManager& manager, const string& x) {
    int count = 0;
    Address* t = manager.head;
    while (t) {
        if (t->name == x) count++;
        t = t->next;
    }
    return count;
}

int main() {
    while (true) {
        try {
            switch (menu()) {
            case 1: current = LIST1; break;
            case 2: current = LIST2; break;
            case 3: current = RESULT; break;
            case 4: insert(lists[current], setElement()); break;
            case 5: {
                string name = inputValidatedString("Enter name: ", "", false, "");
                deleteElement(lists[current], name);
                break;
            }
            case 6: {
                Address* t = lists[current].head;
                while (t) {
                    cout << t->name << " | " << t->city << endl;
                    t = t->next;
                }
                system("pause");
                break;
            }
            case 7: {
                string filename = "task2_8.bin";
                saveToFile(lists[current], filename);
                break;
            }
            case 8: {
                string filename = "task2_8.bin";
                loadFromFile(lists[current], filename);
                break;
            }
            case 9: {
                string name = inputValidatedString("Enter name to count: ", "", false, "");
                cout << "Count: " << countX(lists[current], name) << endl;
                system("pause");
                break;
            }
            case 0:
                return 0;
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            system("pause");
        }
    }
}