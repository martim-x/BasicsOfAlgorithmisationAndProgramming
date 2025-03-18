#include "List.h"
#include <iostream>
using namespace std;

List::~List() {
    DeleteList();
}

// Вставка элемента в начало списка
bool List::Insert(Person* data) {
    Element* newElem = new Element(nullptr, data, Head);
    if (Head != nullptr)
        Head->Prev = newElem;
    Head = newElem;
    return true;
}

// Вставка элемента в конец списка
bool List::InsertEnd(Person* data) {
    if (Head == nullptr) {
        return Insert(data);
    }
    Element* curr = Head;
    while (curr->Next != nullptr)
        curr = curr->Next;
    Element* newElem = new Element(curr, data, nullptr);
    curr->Next = newElem;
    return true;
}

// Поиск элемента по имени
Element* List::Search(const string& name) {
    Element* curr = Head;
    while (curr != nullptr) {
        if (curr->Data->name == name)
            return curr;
        curr = curr->Next;
    }
    return nullptr;
}

// Удаление первого элемента с заданным именем
bool List::Delete(const string& name) {
    Element* elem = Search(name);
    if (elem == nullptr)
        return false;
    if (elem->Prev != nullptr)
        elem->Prev->Next = elem->Next;
    else
        Head = elem->Next;
    if (elem->Next != nullptr)
        elem->Next->Prev = elem->Prev;
    delete elem->Data;
    delete elem;
    return true;
}

// Вывод списка с использованием функции печати
void List::PrintList(std::function<void(Person*)> printFunc) {
    Element* curr = Head;
    while (curr) {
        printFunc(curr->Data);
        curr = curr->Next;
    }
}

// Подсчёт элементов в списке
int List::CountList() {
    int count = 0;
    Element* curr = Head;
    while (curr != nullptr) {
        count++;
        curr = curr->Next;
    }
    return count;
}

// Удаление всего списка
bool List::DeleteList() {
    Element* curr = Head;
    while (curr != nullptr) {
        Element* next = curr->Next;
        delete curr->Data;
        delete curr;
        curr = next;
    }
    Head = nullptr;
    return true;
}
