
#include <iostream>
using namespace std;


struct Data {
    int key;
    void print();
};

enum CompareResult {
    LESS = -1, EQUAL = 0, GREATER = 1
};

struct Heap {
    int currentSize;
    int capacity;
    void** storage;
    CompareResult(*compare)(void*, void*);

    Heap(int maxSize, CompareResult(*comparator)(void*, void*)) :
        currentSize(0), capacity(maxSize), compare(comparator) {
        storage = new void* [capacity];
    }

    int left(int index) const;
    int right(int index) const;
    int parent(int index) const;
    void swap(int i, int j);
    void siftUp(int index);
    void heapify(int index);

    bool isFull() const { return currentSize >= capacity; }
    bool isEmpty() const { return currentSize == 0; }
    void insert(void* element);
    void* extractMax();
    void* extractMin();
    void* extractByIndex(int index);
    void display() const;
};

Heap createHeap(int capacity, CompareResult(*comparator)(void*, void*));
Heap mergeHeaps(const Heap& h1, const Heap& h2);
