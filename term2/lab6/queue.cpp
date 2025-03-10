#include "queue.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Функция создания очереди заданного размера
Queue createQueue(int n) {
    return Queue(n); // Инициализируем очередь с заданным размером
}

// Функция копирования очереди
Queue copyQueue(const Queue& q) {
    Queue newQueue(q.Size - 1);  // Создаем очередь с таким же размером, минус 1 для учета цикличности
    newQueue.Head = q.Head;
    newQueue.Tail = q.Tail;

    // Копируем все элементы из старой очереди в новую
    int i = q.Head;
    while (i != q.Tail) {
        newQueue.Data[i] = q.Data[i];
        i = (i + 1) % q.Size;
    }

    return newQueue;
}

// Функция добавления элемента в очередь
bool enQueue(Queue& q, void* x) {
    if (q.isFull()) {
        cout << "Queue is full!" << endl;
        return false;  // Очередь полна, добавление невозможно
    }

    // Добавляем новый элемент в очередь
    q.Data[q.Tail] = x;
    q.Tail = (q.Tail + 1) % q.Size;  // Обновляем хвост с учетом цикличности
    return true;
}

// Функция удаления первого элемента из очереди
void* delQueue(Queue& q) {
    if (q.isEmpty()) {
        cout << "Queue is empty!" << endl;
        return nullptr;  // Очередь пуста, ничего не удаляем
    }

    // Извлекаем первый элемент
    void* item = q.Data[q.Head];
    q.Head = (q.Head + 1) % q.Size;  // Обновляем голову с учетом цикличности
    return item;
}

// Функция получения первого элемента очереди без удаления
void* peekQueue(const Queue& q) {
    if (q.isEmpty()) {
        cout << "Queue is empty!" << endl;
        return nullptr;  // Очередь пуста, ничего не возвращаем
    }

    // Возвращаем первый элемент, не удаляя его
    return q.Data[q.Head];
}

// Функция очистки очереди (удаляет все элементы)
int clearQueue(Queue& q) {
    // Простой способ очистки — сбросить индексы головы и хвоста
    q.Head = q.Tail = 0;
    return 0;  // Успешное выполнение
}

// Функция освобождения памяти, выделенной под очередь
void releaseQueue(Queue& q) {
    delete[] q.Data;  // Освобождаем память, выделенную под данные очереди
    q.Data = nullptr;  // Обнуляем указатель
}

