#include "ArrayList.h"
#include <HashTable.h>
#include <iostream>

using namespace std;

HashTable::HashTable(int k) {
    capacity = k;
    size = 0;
    for (int i = 0; i < k; i++) {
        table.append(ArrayList<int>());
    }
}

void HashTable::inflate() {
    int news = capacity * 2;
    ArrayList<ArrayList<int>> nt;
    for (int i = 0; i < news; i++) {
        nt.append(ArrayList<int>());
    }
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < table[i].size(); j++) {
            int index = table[i][j] % news;
            if (index < 0) {
                index += news;
            }
            nt[index].append(table[i][j]);
        }
    }
    capacity = news;
    table = nt;
}

void HashTable::insert(int value) {
    if (size / capacity >= 3) {
        inflate();
    }
    int index = f(value);
    table[index].append(value);
    size += 1;
}

bool HashTable::search(int value) {
    int index = f(value);
    bool found = table[index].search(value);
    return found;
}

int HashTable::f(int x) {
    // Your code goes here...
    // cout << "x: " << x << ", capacity: " << capacity << endl;
    int index = x % capacity;
    if (index < 0) {
        index += capacity;
    }
    // cout << "Return: " << index << endl;
    return index;
}