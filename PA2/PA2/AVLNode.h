#ifndef AVLNODE_H
#define AVLNODE_H

template<typename T>
class AVLNode {
public:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const T& data, AVLNode* left = nullptr, AVLNode* right = nullptr, int height = 1)
        : data(data), left(left), right(right), height(height) {}
    ~AVLNode() {
        delete left;
        delete right;
    }
};

#endif 
