#ifndef BST_H
#define BST_H
#include <cstddef>
#include <iostream>

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
    Node *root;

    Node *search_helper(Node *r, int x) {
        if (r == nullptr) {
            return nullptr;
        } else {
            if (r->data == x) {
                return r;
            } else {
                if (x < r->data) {
                    return search_helper(r->left, x);
                } else {
                    return search_helper(r->right, x);
                }
            }
        }
    }

    Node *insert_helper(Node *root, int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            if (value < root->data) {
                root->left = insert_helper(root->left, value);
            } else {
                root->right = insert_helper(root->right, value);
            }
        }
        return root;
    }
    void traverse_helper(Node *root) {
        if (root != nullptr) {
            traverse_helper(root->left);
            std::cout << root->data << " ";
            traverse_helper(root->right);
        }
    }
    Node *max_helper(Node *root) {
        if (root == nullptr) {
            return nullptr;
        } else {
            if (root->right == nullptr) {
                return root;
            } else {
                return max_helper(root->right);
            }
        }
    }
    Node *min_helper(Node *curr) {
        if (curr == nullptr) {
            return nullptr;
        } else {
            while (curr->left != nullptr) {
                curr = curr->left;
            }

            return curr;
        }

        return nullptr;
    }

    void copy_helper(Node *root) {
        if (root != nullptr) {
            insert(root->data);
            copy_helper(root->left);
            copy_helper(root->right);
        }
    }

public:
    BinarySearchTree() { root = nullptr; }

    BinarySearchTree(const BinarySearchTree &other) { copy_helper(other.root); }

    void insert(int value) { root = insert_helper(root, value); }

    void traverse() { traverse_helper(root); }

    Node *search(int x) { return search_helper(root, x); }

    Node *min() {
        // Your code here
        return min_helper(root);
    }

    Node *max() {
        // Your code here
        return max_helper(root);
    }

    Node *remove_helper(Node *root, int key) {
        if (root == nullptr)
            return nullptr;
        if (key < root->data) {
            root->left = remove_helper(root->left, key);
        } else if (key > root->data) {
            root->right = remove_helper(root->right, key);
        } else {
            
            // case 1: no child
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // case 2: one child (right only)
            else if (root->left == nullptr) {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            // case 2: one child (left only)
            else if (root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            // case 3: two children
            else {
                Node *succ =
                    min_helper(root->right); // smallest in right subtree
                root->data = succ->data;     // copy value
                root->right =
                    remove_helper(root->right, succ->data); // delete succ
            }
        }
        return root;
    }

    Node *successor(Node *start) {

        Node *current = root;
        Node *succ = nullptr;

        while (current) {
            if (start->data < current->data) {
                succ = current;
                current = current->left;
            } else if (start->data > current->data) {
                current = current->right;
            } else {
                break;
            }
        }
        return succ;
    }

    Node *findParent(Node *start) {
        if (start == nullptr) {
            return nullptr;
        }
        if (start == root) {
            return nullptr;
        }

        Node *temp = root;
        Node *parent = root;

        while (temp != start) {
            parent = temp;
            if (start->data < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return parent;
    }

    void remove(Node *node) {
        
        remove_helper(root, node->data);
    }
    

    // Call the function to display the tree and leave some space afterwards
    void draw() {
        displayTree(root, 0, 0);
        std::cout << std::endl << std::endl;
    }
};

#endif