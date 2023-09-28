#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
    T value;              // Value of the node
    Node* left;           // Pointer to the left child node
    Node* right;          // Pointer to the right child node

    // Constructor initializes the node with a value and null pointers
    Node(T val) : value(val), left(nullptr), right(nullptr) {}

    // Destructor resets the node's value and pointers
    ~Node() {
        value = 0;
        left = right = nullptr;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {
protected:
    Node<T>* _root;  // Root of the tree nodes

    // Helper function to add a value to the tree
    void addHelper(Node<T>* root, T val);

    // Helper function to print the tree in order
    void printInOrderHelper(Node<T>* root);

    // Helper function to count the number of nodes in the tree
    int nodesCountHelper(Node<T>* root);

    // Helper function to get the height of the tree
    int heightHelper(Node<T>* root);

    // Helper function to delete a value from the tree
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value);

    // Helper function to destroy the tree
    void destroyTree(Node<T>* node);

    // Helper function to check if the tree contains a value
    bool containsHelper(Node<T>* node, T value);

    // Helper function to print the tree level by level
    void printLevelOrderHelper(Node<T>* node, int level);

    // Helper function to get the maximum depth of the tree
    int maxDepth(Node<T>* node);

    // Helper function to print the maximum path in the tree
    void printMaxPathHelper(Node<T>* node, int& maxSum, int currentSum, vector<T>& path, vector<T>& maxPath, int level);

public:
    // Basic initialization constructor
    BST() : _root(nullptr) {}

    // Destructor frees all nodes in the tree
    ~BST() { destroyTree(_root); }

    // Function to add a value to the tree
    void add(T val);

    // Function to print the tree
    void print();

    // Function to print the tree level by level
    void printLevelOrder();

    // Function to count the number of nodes in the tree
    int nodesCount();

    // Function to get the height of the tree
    int height();

    // Function to print the maximum path in the tree
    void printMaxPath();

    // Function to delete a value from the tree
    bool deleteValue(T value);

    // Function to check if the tree contains a value
    bool contains(T value);
};

template <typename T>
void BST<T>::addHelper(Node<T>* root, T val) {
    if (root->value > val) {
        if (!root->left)
            root->left = new Node<T>(val);
        else
            addHelper(root->left, val);
    }
    else {
        if (!root->right)
            root->right = new Node<T>(val);
        else
            addHelper(root->right, val);
    }
}

template <typename T>
void BST<T>::printInOrderHelper(Node<T>* root) {
    if (!root) return;
    printInOrderHelper(root->left);
    cout << root->value << ' ';
    printInOrderHelper(root->right);
}

template <typename T>
int BST<T>::nodesCountHelper(Node<T>* root) {
    return root ? 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right) : 0;
}

template <typename T>
int BST<T>::heightHelper(Node<T>* root) {
    return root ? 1 + max(heightHelper(root->left), heightHelper(root->right)) : -1;
}

template <typename T>
bool BST<T>::deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
    if (!current) return false;
    if (current->value == value) {
        if (current->left == nullptr || current->right == nullptr) {
            Node<T>* temp = current->left;
            if (current->right) temp = current->right;
            if (parent) {
                if (parent->left == current) {
                    parent->left = temp;
                }
                else {
                    parent->right = temp;
                }
            }
            else {
                this->_root = temp;
            }
        }
        else {
            Node<T>* validSubs = current->right;
            while (validSubs->left) {
                validSubs = validSubs->left;
            }
            T temp = current->value;
            current->value = validSubs->value;
            validSubs->value = temp;
            return deleteValueHelper(current, current->right, temp);
        }
        delete current;
        return true;
    }
    return deleteValueHelper(current, current->left, value) ||
        deleteValueHelper(current, current->right, value);
}

template <typename T>
void BST<T>::destroyTree(Node<T>* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T>
bool BST<T>::containsHelper(Node<T>* node, T value) {
    if (!node) return false;
    if (node->value == value) return true;
    return containsHelper(node->left, value) || containsHelper(node->right, value);
}

template <typename T>
void BST<T>::printLevelOrderHelper(Node<T>* node, int level) {
    if (!node) return;
    if (level == 1) {
        cout << node->value << ' ';
    }
    else if (level > 1) {
        printLevelOrderHelper(node->left, level - 1);
        printLevelOrderHelper(node->right, level - 1);
    }
}

template <typename T>
int BST<T>::maxDepth(Node<T>* node) {
    return node ? 1 + max(maxDepth(node->left), maxDepth(node->right)) : 0;
}

template <typename T>
void BST<T>::printMaxPath() {
    int maxSum = numeric_limits<T>::min();
    vector<T> path;
    vector<T> maxPath;
    path.resize(maxDepth(_root));
    maxPath.resize(maxDepth(_root));
    printMaxPathHelper(_root, maxSum, 0, path, maxPath, 0);
    for (int i = 0; i < maxPath.size() && maxPath[i] != 0; i++) {
        cout << maxPath[i] << ' ';
    }
    cout << endl;
}

template <typename T>
void BST<T>::printMaxPathHelper(Node<T>* node, int& maxSum, int currentSum, vector<T>& path, vector<T>& maxPath, int level) {
    if (!node) return;
    path[level] = node->value;
    currentSum += node->value;
    if (!node->left && !node->right) { 
        if (currentSum > maxSum) {
            maxSum = currentSum;
            for (int i = 0; i <= level; i++) {
                maxPath[i] = path[i];
            }
        }
    }
    else {
        if (node->left) printMaxPathHelper(node->left, maxSum, currentSum, path, maxPath, level + 1);
        if (node->right) printMaxPathHelper(node->right, maxSum, currentSum, path, maxPath, level + 1);
    }
   
    path[level] = 0;
}



template <typename T>
void BST<T>::add(T val) {
    if (this->_root) {
        this->addHelper(this->_root, val);
    }
    else {
        this->_root = new Node<T>(val);
    }
}

template <typename T>
void BST<T>::print() {
    printInOrderHelper(this->_root);
    cout << endl;
}

template <typename T>
void BST<T>::printLevelOrder() {
    int height = maxDepth(_root);
    for (int i = 1; i <= height; i++) {
        printLevelOrderHelper(_root, i);
    }
    cout << endl;
}

template <typename T>
int BST<T>::nodesCount() {
    return nodesCountHelper(this->_root);
}

template <typename T>
int BST<T>::height() {
    return heightHelper(this->_root);
}

template <typename T>
bool BST<T>::deleteValue(T value) {
    return this->deleteValueHelper(nullptr, this->_root, value);
}

template <typename T>
bool BST<T>::contains(T value) {
    return containsHelper(this->_root, value);
}

#endif



