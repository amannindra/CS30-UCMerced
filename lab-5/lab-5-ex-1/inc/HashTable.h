#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <ArrayList.h>

class HashTable {
    int capacity;   // The number of buckets
    int size;       // The number of elements stored

    ArrayList<ArrayList<int>> table;    // Each bucket is an array list, allowing us to
                                        // store as many elements as we want in it

    int f(int x);       // The hash function, should be good and fast
    void inflate();     // Should double capacity of hash table

public:
    HashTable(int k = 10);      // By default, capacity should be 10, otherwise user can specify
    
    void insert(int value);
    bool search(int value);

    friend std::ostream& operator<<(std::ostream& os, const HashTable& table);
    friend struct TestProgram;
};

inline std::ostream& operator<<(std::ostream& os, const HashTable& ht){
    for (int i = 0; i < ht.capacity; i++){
        os << i << ": " << ht.table[i] << "\n";
    }

    return os;
}

#endif