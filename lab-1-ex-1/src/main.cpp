#include <iostream>
#include <ArrayList.h>
using namespace std;

int main() {

    ArrayList<int> list;
          list.append(99);
        list.append(27);
        list.append(14);
        list.append(42);
        list.append(72);
    // cout << list << endl;
    // list.prepend(5);
    cout << "before list" << list << endl;
    list.removeFirst();
    list.removeFirst();


    cout << "final list" << list << endl;

    return 0;
}