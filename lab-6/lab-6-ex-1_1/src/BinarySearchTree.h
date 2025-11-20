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
    }

    void copy_helper(Node *root) {
        if (root != nullptr) {
            insert(root->data);
            copy_helper(root->left);
            copy_helper(root->right);
        }
    }
    // Node *remove_helper(Node *root, int key) {
    //     if (root == nullptr)
    //         return nullptr;
    //     if (key < root->data) {
    //         root->left = remove_helper(root->left, key);
    //     } else if (key > root->data) {
    //         root->right = remove_helper(root->right, key);
    //     } else {

    //         // case 1: no child
    //         if (root->left == nullptr && root->right == nullptr) {
    //             delete root;
    //             return nullptr;
    //         }
    //         // case 2: one child (right only)
    //         else if (root->left == nullptr) {
    //             Node *temp = root->right;
    //             delete root;
    //             return temp;
    //         }
    //         // case 2: one child (left only)
    //         else if (root->right == nullptr) {
    //             Node *temp = root->left;
    //             delete root;
    //             return temp;
    //         }
    //         // case 3: two children
    //         else {
    //             Node *temp = min_helper(root->right);
    //             root->data = temp->data;
    //             root->right = remove_helper(root->right, temp->data);
    //         }
    //     }
    //     return root;
    // }

public:
    BinarySearchTree() { root = nullptr; }

    BinarySearchTree(const BinarySearchTree &other) {
        root = nullptr;
        copy_helper(other.root);
    }

    void insert(int x) { root = insert_helper(root, x); }

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

    Node *successor(Node *start) {
 
        Node *succ = nullptr;
        Node *current = root;

        if (start->right != nullptr) {
            return min_helper(start->right);
        }
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
        if (node == nullptr)
            return;
        if (node->left == nullptr && node->right == nullptr) {
            Node *parent = findParent(node);
            if (parent == nullptr) {
                root = nullptr;
            } else if (parent->left == node) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete node;
        } else if (node->left == nullptr || node->right == nullptr) {
            Node *child = nullptr;
            if (node->left != nullptr) {
                child = node->left;
            } else {
                child = node->right;
            }
            Node *parent = findParent(node);

            if (parent == nullptr) {
                root = child;
            } else {

                if (parent->left == node) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                delete node;
            }

        } else {
            Node *success = successor(node);
            node->data = success->data;
            remove(success);
        }
    }

    // A function to display the tree graphically
    void displayTree(Node *r, int level, int direction) {
        // Don't worry about this function, just use it
        if (r != NULL) {
            displayTree(r->right, level + 1, 1);

            for (int i = 0; i < level - 1; i++) {
                std::cout << "   ";
            }
            if (level > 0) {
                if (direction == 1) {
                    std::cout << " /--";
                } else {
                    std::cout << " \\--";
                }
            }
            std::cout << r->data;
            std::cout << std::endl;
            level++;

            displayTree(r->left, level, -1);
        }
    }

    void draw() {
        displayTree(root, 0, 0);
        std::cout << std::endl << std::endl;
    }
};

#endif