#ifndef QUEUE_H
#define QUEUE_H

#include <LinkedList.h>

template <class T>
class Queue : public LinkedList<T> {
    void append(T) {}
    void prepend(T) {}
    T removeFirst() {}
    T removeLast() {}

public:
    void enqueue(T value) {
        LinkedList<T>::append(value);
    }

    T dequeue() {
        return LinkedList<T>::removeFirst();
    }

    T peek() {
        return LinkedList<T>::operator[](0);
    }

    bool isEmpty() const {
        return LinkedList<T>::size() == 0;
    }
};

#endif