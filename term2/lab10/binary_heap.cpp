#include "binary_heap.h"
#include <iostream>
#include <iomanip>

void Data::print() {
    std::cout << key;
}


Heap createHeap(int capacity, CompareResult(*comparator)(void*, void*)) {
    return Heap(capacity, comparator);
}

int Heap::left(int index) const {
    int child = 2 * index + 1;
    return child < currentSize ? child : -1;
}

int Heap::right(int index) const {
    int child = 2 * index + 2;
    return child < currentSize ? child : -1;
}

int Heap::parent(int index) const {
    return index > 0 ? (index - 1) / 2 : -1;
}

void Heap::swap(int i, int j) {
    void* temp = storage[i];
    storage[i] = storage[j];
    storage[j] = temp;
}

void Heap::siftUp(int index) {
    while (index > 0 && compare(storage[parent(index)], storage[index]) == LESS) {
        swap(index, parent(index));
        index = parent(index);
    }
}

void Heap::heapify(int index) {
    int largest = index;
    int l = left(index);
    int r = right(index);

    if (l != -1 && compare(storage[l], storage[largest]) == GREATER)
        largest = l;
    if (r != -1 && compare(storage[r], storage[largest]) == GREATER)
        largest = r;

    if (largest != index) {
        swap(index, largest);
        heapify(largest);
    }
}

void Heap::insert(void* element) {
    if (!isFull()) {
        storage[currentSize] = element;
        siftUp(currentSize);
        currentSize++;
    }
}

void* Heap::extractMax() {
    if (isEmpty()) return nullptr;

    void* root = storage[0];
    storage[0] = storage[--currentSize];
    heapify(0);
    return root;
}

void* Heap::extractMin() {
    if (isEmpty()) return nullptr;

    int minIndex = 0;
    for (int i = 1; i < currentSize; i++) {
        if (compare(storage[i], storage[minIndex]) == LESS)
            minIndex = i;
    }

    void* min = storage[minIndex];
    storage[minIndex] = storage[--currentSize];
    heapify(minIndex);
    return min;
}

void* Heap::extractByIndex(int index) {
    if (index < 0 || index >= currentSize) return nullptr;

    void* element = storage[index];
    storage[index] = storage[--currentSize];
    heapify(index);
    siftUp(index);
    return element;
}

void Heap::display() const {
    int level = 0;
    int elementsInLevel = 1;
    int count = 0;

    std::cout << "\nHeap Structure:\n";
    for (int i = 0; i < currentSize; i++) {
        if (count == 0)
            std::cout << std::string((1 << (level + 1)) - 2, ' ');

        Data* item = static_cast<Data*>(storage[i]);
        std::cout << std::setw(2) << item->key;

        if (++count == elementsInLevel) {
            std::cout << "\n";
            level++;
            elementsInLevel *= 2;
            count = 0;
        }
        else {
            std::cout << std::string((1 << (level + 2)) - 2, ' ');
        }
    }
    std::cout << "\n";
}

Heap mergeHeaps(const Heap& h1, const Heap& h2) {
    int newCapacity = h1.capacity + h2.capacity;
    Heap newHeap(newCapacity, h1.compare);

    for (int i = 0; i < h1.currentSize; i++)
        newHeap.storage[newHeap.currentSize++] = h1.storage[i];

    for (int i = 0; i < h2.currentSize; i++)
        newHeap.storage[newHeap.currentSize++] = h2.storage[i];

    for (int i = newHeap.parent(newHeap.currentSize - 1); i >= 0; i--)
        newHeap.heapify(i);

    return newHeap;
}
