#include <LinkedList.h>
#include <iostream>
using namespace std;

int main() {

    LinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    int val = list.remove(1);
    cout << "Val: " << val << endl;
    cout << list << endl;

    return 0;
}