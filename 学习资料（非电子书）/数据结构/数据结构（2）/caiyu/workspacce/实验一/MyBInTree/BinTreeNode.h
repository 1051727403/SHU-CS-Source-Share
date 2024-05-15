//
// Created by Silence on 2022/3/11.
//

#ifndef MYTREE_BINTREENODE_H
#define MYTREE_BINTREENODE_H

#include "Assistance.h"

template<typename T>
struct BinTreeNode {
    T data;
    BinTreeNode<T> *leftChild;
    BinTreeNode<T> *rightChild;

    BinTreeNode(T data, BinTreeNode<T> *leftChild = NULL, BinTreeNode<T> *rightChild = NULL);
    BinTreeNode();
};
template<typename T>
BinTreeNode<T>::BinTreeNode(T data, BinTreeNode<T> *leftChild, BinTreeNode<T> *rightChild):data(data),
                                                                                           leftChild(leftChild),
                                                                                           rightChild(rightChild) {}
template<typename T>
BinTreeNode<T>::BinTreeNode() {
    leftChild = rightChild = NULL;
}

#endif //MYTREE_BINTREENODE_H
