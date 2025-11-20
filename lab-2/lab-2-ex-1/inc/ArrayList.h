#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>

/*
    Forward declaration of the class template ArrayList<T>.

    At this point the compiler knows there is something called ArrayList<T>,
    a class template called ArrayList.

    The compiler does not need to know exactly what ArrayList is at this point,
    it just needs to know that there is something like that.

    We need to do this because of the function template definition below,
    which needs to take in an argument of type ArrayList<T>. That's why 
    we had to pre-declare it here.
*/
template <class T>
class ArrayList;



/*
    This needs to be declared before the class ArrayList, so that it
    can be used inside the class to specify that we want it as a friend.
    
    It takes in the class template ArrayList as a parameter,
    so it needs to be defined after the class declaration.
*/
template <class T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list);



/*
    Array list is a class template, allowing us to store data of any type
*/
template <class T>
class ArrayList {
protected:
    int count;
    int capacity;
    T* data;

    // Helper function to double our capacity while preserving the data
    void inflate() {
        capacity *= 2;

        T* old = data;
        data = new T[capacity];

        for (int i = 0; i < count; i++) {
            data[i] = old[i];
        }

        delete[] old;
    }

    // Helper function to reduce our capacity by half while preserving the data
    void deflate() {
        capacity /= 2;

        T* old = data;
        data = new T[capacity];

        for (int i = 0; i < count; i++) {
            data[i] = old[i];
        }

        delete[] old;
    }

public:
    // Default constructor: initializes capacity to 1 (will be increased if necessary)
    ArrayList() {
        count = 0;
        capacity = 1;
        data = new T[capacity];
    }

    // Copy constructor: needed because we store data on the heap
    ArrayList(const ArrayList& other) {
        count = other.count;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i < other.count; i++) {
            data[i] = other.data[i];
        }
    }


    // Overloaded assignment operator: needed because we store data on the heap
    ArrayList& operator=(const ArrayList& other) {
        if (capacity == other.capacity) {
            count = other.count;

            for (int i = 0; i < other.count; i++) {
                data[i] = other.data[i];
            }
        } else {
            T* old = data;

            count = other.count;
            capacity = other.capacity;
            data = new T[capacity];

            for (int i = 0; i < other.count; i++) {
                data[i] = other.data[i];
            }

            delete[] old;
        }

        return *this;
    }

    // Appends a value to the end of the list.
    // We guarantee that there is always space to add one more.
    // The inflate() function increases the capacity if necessary.
    void append(T value) {
        data[count] = value;
        count++;

        if (count == capacity) {
            inflate();
        }
    }

    void prepend(T value) {
        for (int i = count; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value;

        count++;
        if (count == capacity) {
            inflate();
        }
    }

    T removeFirst() {
        if (count == 0) {
            throw std::logic_error("ArrayList is empty!");
        }

        T target = data[0];

        for (int i = 0; i < count - 1; i++) {
            data[i] = data[i + 1];
        }

        count--;
        if (capacity/2 > count) {
            deflate();
        }

        return target;
    }

    T removeLast() {
        if (count == 0) {
            throw std::logic_error("ArrayList is empty!");
        }

        T target = data[count - 1];
        
        count--;
        if (capacity/2 > count) {
            deflate();
        }

        return target;
    }

    void insert(int index, T value){
        if (index < 0 || index > count) {
            throw std::logic_error("Index is out of bounds");
        }

        for (int i = count; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;

        count++;
        if (count == capacity) {
            inflate();
        }
    }

    bool search (T value) const {
        for (int i = 0; i < count; i++){
            if (value == data[i]){
                return true;
            }
        }
        return false;
    }

    // Overloaded [] operator: allows us to access and manipulate (read/write) any
    // element in a valid position in the ArrayList
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::logic_error("Index is out of bounds");
        }
        return data[index];
    }

    // Getter: returns the number of elements in the ArrayList (not the capacity)
    int getSize() const {
        return count;
    }

    // Getter: returns the capacity of the list
    int getCapacity() const {
        return capacity;
    }

    // Destructor: responsible for releasing the memory used on the heap
    ~ArrayList() {
        delete[] data;
    }

    // Friendship declaration for overloaded << operator.
    friend std::ostream& operator<< <T>(std::ostream& os, const ArrayList<T>& list);
    
    // Friendship declaration for unit testing (we want access to everything when testing).
    friend struct TestArrayList;
};



/*
    The overloaded << operator allows us to cout our ArrayList.

    It is a function template because we wish to be able to pass a
    a class template as a parameter
*/
template <class T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
    os << "[";
    for (int i = 0; i < list.count; i++) {
        os << list.data[i];
        if (i < list.count - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif