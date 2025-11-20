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
        append(1000);
        for(int i = getSize(); i > 0 ; i--) {
            // std::cout << "Replacing " << data[i] << " with " << data[i-1] << std::endl;
            data[i] = data[i - 1];
        };

        data[0] = value;
    }

    T removeFirst() {
        if (getSize() == 0){
            throw std::logic_error("Size list is size 0");

            return T();
        }

        for(int i = 1; i < getSize(); i++) {
            data[i - 1] = data[i];
        };
        removeLast();
        std::cout << capacity << std::endl;
        if (getSize() * 2 < capacity) {
            std::cout << "deflating removeFirst" << std::endl;
            deflate();
        }
    
       
        return T();
    }

    T removeLast() {
        if (getSize() == 0){
            throw std::logic_error("Size list is size 0");
            return T();
        }else {
        count--;
        // capacity--;

        if (getSize() * 2 < capacity) {
            std::cout << "deflating removelast" << std::endl;
            deflate();
        }

        std::cout << capacity << std::endl;
        return T();}
    }

    void insert(int index, T value){

        if (getSize() == 0 && index == 0) {
            std::cout << "Getsize and index is 0" << std::endl;
            append(value);
        }
        else if (index > getSize()) {
            throw std::logic_error("Index is too big for list");
        }
        


        else if (index == getSize()) {
            std::cout << "Index is the last digit" << std::endl;
            data[index] = value;
            throw std::logic_error("Index is the last digit");
        }
        else {
        
            int last = data[-1];
            append(1000000);

            for(int i = getSize() - 1; i > index - 1; i--) {
                // std::cout << "Replacing " << data[i + 1] << " with " << data[i] << std::endl;
                data[i + 1] = data[i];
            }
            data[index] = value;

            std::cout << "Append " << last << std::endl;
            // append(last);
        }

    }

    void sort(){
        // Your code goes here...
        int n = getSize();
        bool swapped;
    
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int temp = data[j];

                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                    swapped = true;
                }
            }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }

    }

    // Overloaded [] operator: allows us to access and manipulate (read/write) any
    // element in a valid position in the ArrayList
    T& operator[](int index) {
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