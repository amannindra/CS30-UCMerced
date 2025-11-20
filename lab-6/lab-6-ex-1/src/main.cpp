#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

// Do not modify the contents of this file

int main() {
    cout << "------------------" << endl;
    BinarySearchTree tree;

    tree.insert(10);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);

    tree.draw();
    cout << "Before" << endl;
    tree.remove(tree.search(7));
    cout << "after" << endl;
    tree.draw();

    // BinarySearchTree backup = tree;

    // tree.insert(8);

    // tree.draw();

    // backup.draw();

    // backup.remove(backup.search(7));

    // backup.draw();

    return 0;
}