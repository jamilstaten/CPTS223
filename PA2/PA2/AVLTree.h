#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <algorithm>  // std::max
#include <cmath>  // std::abs

template<typename T>
class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    // Public Member Functions
    int height() const { return height(root); }
    void insert(const T& data) { insert(root, data); }
    bool contains(const T& data) const { return contains(root, data); }
    bool validate() const { return validate(root); }

private:
    AVLNode<T>* root;

    // Private Member Functions
    int height(AVLNode<T>* node) const {
        return node ? node->height : 0;
    }

    void insert(AVLNode<T>*& node, const T& data) {
        if (!node) {
            node = new AVLNode<T>(data);
        }
        else if (data < node->data) {
            insert(node->left, data);
        }
        else if (data > node->data) {
            insert(node->right, data);
        }
        balance(node);
    }

    bool contains(AVLNode<T>* node, const T& data) const {
        if (!node) return false;
        else if (data < node->data) return contains(node->left, data);
        else if (data > node->data) return contains(node->right, data);
        else return true;  
    }

    bool validate(AVLNode<T>* node) const {
        if (!node) return true;  
        int balanceFactor = height(node->left) - height(node->right);
        if (std::abs(balanceFactor) > 1) return false;  
        return validate(node->left) && validate(node->right);
    }

    void clear(AVLNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void balance(AVLNode<T>*& node) {
        if (!node) return;

        // Update height
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Balance factor and rotation
        int balanceFactor = height(node->left) - height(node->right);

        if (balanceFactor > 1) {  // Left heavy
            // Right rotation
            if (height(node->left->right) > height(node->left->left)) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
        else if (balanceFactor < -1) {  // Right heavy
            // Left rotation
            if (height(node->right->left) > height(node->right->right)) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
    }

    void rotateLeft(AVLNode<T>*& node) {
        AVLNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));
        node = newRoot;
    }

    void rotateRight(AVLNode<T>*& node) {
        AVLNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));
        node = newRoot;
    }
};

#endif 

