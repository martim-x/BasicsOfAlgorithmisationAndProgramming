#include "queue.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Queue createQueue(int n) {
    return Queue(n);
}


Queue copyQueue(const Queue& q) {
    Queue newQueue(q.Size - 1);
    newQueue.Head = q.Head;
    newQueue.Tail = q.Tail;


    int i = q.Head;
    while (i != q.Tail) {
        newQueue.Data[i] = q.Data[i];
        i = (i + 1) % q.Size;
    }

    return newQueue;
}


bool enQueue(Queue& q, void* x) {
    if (q.isFull()) {
        cout << "Queue is full!" << endl;
        return false;
    }


    q.Data[q.Tail] = x;
    q.Tail = (q.Tail + 1) % q.Size;
    return true;
}


void* delQueue(Queue& q) {
    if (q.isEmpty()) {
        cout << "Queue is empty!" << endl;
        return nullptr;
    }


    void* item = q.Data[q.Head];
    q.Head = (q.Head + 1) % q.Size;
    return item;
}


void* peekQueue(const Queue& q) {
    if (q.isEmpty()) {
        cout << "Queue is empty!" << endl;
        return nullptr;
    }


    return q.Data[q.Head];
}

int clearQueue(Queue& q) {

    q.Head = q.Tail = 0;
    return 0;
}


void releaseQueue(Queue& q) {
    delete[] q.Data;
    q.Data = nullptr;
}

