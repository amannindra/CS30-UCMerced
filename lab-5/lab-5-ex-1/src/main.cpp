#include <iostream>
#include <HashTable.h>
using namespace std;

int main() {
    // You can experiment with your data structure here...

    HashTable hashTable;

    hashTable.insert(1);
    hashTable.insert(3);
    hashTable.insert(5);


    cout << hashTable << endl;

    cout << "works" << endl;

    cout << "Search(3): " << hashTable.search(3) << endl;
    
    return 0;
}
