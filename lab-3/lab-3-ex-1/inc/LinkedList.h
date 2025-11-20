#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>

template <class T> class LinkedList;

template <class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list);

template <class T> struct Link {
    T data;
    Link *next;

    Link() {
        data = 0;
        next = nullptr;
    }

    Link(T data) {
        this->data = data;
        next = nullptr;
    }
};

template <class T> class LinkedList {
    Link<T> *front;
    Link<T> *back;
    int count;

public:
    LinkedList() {
        front = nullptr;
        back = nullptr;
        count = 0;
    }

    LinkedList(const LinkedList &other) {
        front = nullptr;
        back = nullptr;
        count = 0;

        Link<T> *temp = other.front;
        while (temp != nullptr) {
            append(temp->data);
            temp = temp->next;
        }
    }

    LinkedList &operator=(const LinkedList &other) {
        while (count < other.count) {
            append(0);
        }

        while (count > other.count) {
            removeFirst();
        }

        Link<T> *ours = front;
        Link<T> *theirs = other.front;

        while (ours != nullptr) {
            ours->data = theirs->data;
            ours = ours->next;
            theirs = theirs->next;
        }

        return *this;
    }

    T &operator[](int index) {

        if (index < 0 || index >= count) {
            throw std::out_of_range(
                "LinkedList::operator[] index out of range");
        }
        Link<T> *current = front;
        for (int i = 0; i < index; ++i) {
            current = current->next; // safe because of the check above
        }
        std::cout << "returning this index: " << current->data << std::endl;
        return current->data;
    }

    void append(T value) {
        // std::cout << "Value: " << value << std::endl;
        Link<T> *newLink = new Link<T>(value);

        if (front == nullptr) {
            front = newLink;
            back = newLink;
        } else {
            back->next = newLink;
            back = newLink;
        }
        count++;
    }

    void prepend(T value) {
        Link<T> *newLink = new Link<T>(value);

        if (front == nullptr) {
            front = newLink;
            back = newLink;
        } else {
            newLink->next = front;
            // front->prev = newLink;
            front = newLink;
        }
        count++;
    }

    T removeFirst() {
        if (front == nullptr) {
            throw std::logic_error("List is empty");
        } else if (front == back) {
            T target = front->data;

            delete front;
            front = nullptr;
            back = nullptr;
            count--;

            return target;
        } else {
            T target = front->data;

            Link<T> *oldFront = front;
            front = front->next;
            // front->prev = nullptr;
            delete oldFront;
            count--;

            return target;
        }
    }

    T removeLast() {
        if (front == nullptr) {
            throw std::logic_error("List is empty");
        } else if (front == back) {
            T target = front->data;
            delete front;
            front = nullptr;
            back = nullptr;
            count--;

            return target;
        } else {
            // T target = back->data;

            Link<T> *current = front;
            Link<T> *previous = nullptr;

            int i = 0;
            while (i < count - 1) {

                previous = current;
                current = current->next;
                i += 1;
            };
            current = previous->next;

            T target = current->data;
            std::cout << "Previous data: " << target << std::endl;
            delete current;


            back = previous;
            back->next = nullptr;
            count--;

            return target;
        }
    }

    void reverse() {

        Link<T> *cur = front;
        Link<T> *next = nullptr;
        Link<T> *prev = nullptr;

        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        front = prev;
    }

    void insert(T value, int index) {
        if (index < 0 || index > count) {
             throw std::logic_error("Index out of range");
        }

        if (index == 0){
            prepend(value);
            return;
        }
         

        Link<T>* current = front;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next; // safe due to bounds check above
        }

        Link<T>* val = new Link<T>(value);
        val->next = current->next;
        current->next = val;

        if (val->next == nullptr) {
            back = val;             // inserting at the end
        }
        ++count;
        }

    T remove(int index) {

        if (front == nullptr) {
            throw std::logic_error("List is empty");
        }
        else if (index > count - 1 || index < 0) {
                        std::cout << "dfddsdsds" << std::endl;

            throw std::logic_error("Index too high");
        }
        else if (front == back) {
            std::cout << "dfd" << std::endl;
            return removeFirst();
        }
        else {
                              std::cout << "dffdsfdsdfdssddsdsds" << std::endl;

            if (index == 0){
                // removeFirst();
                Link<T> *current = front;
                std::cout << "First value: " << current << std::endl;
                int num = current->data;
                removeFirst();
                std::cout << "Returning current->data: " << num << std::endl;
                return num;
                
            }

            T target = front->data;

            Link<T> *previous = front;
            Link<T> *current = front;

            for (int i = 0; i < index; i++) {
                previous = current;
                current = current->next;
            }
            std::cout << "Previous->next: " <<  previous->next << std::endl;
            std::cout << "current->next: " <<  current->next << std::endl;

            previous->next = current->next; 
            target = current->data;
            delete current;
            count--;

            return target;
        }
    }

    int getSize() const { return count; }

    ~LinkedList() {
        while (front != nullptr) {
            removeFirst();
        }
    }

    friend std::ostream &operator<< <>(std::ostream &os,
                                       const LinkedList<T> &list);
    friend struct TestLinkedList;
};

template <class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
    Link<T> *temp = list.front;

    while (temp != nullptr) {
        os << temp->data;
        if (temp->next != nullptr) {
            os << " -> ";
        }
        temp = temp->next;
    }

    return os;
}

#endif