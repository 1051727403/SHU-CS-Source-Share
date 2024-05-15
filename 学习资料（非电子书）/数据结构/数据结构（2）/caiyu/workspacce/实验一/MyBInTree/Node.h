//
// Created by Silence on 2022/3/11.
//

#ifndef MYTREE_NODE_H
#define MYTREE_NODE_H

#include<iostream>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T> *next;

    Node(T data, Node<T> *next = NULL);

    Node();

};
template<typename T>
Node<T>::Node(T data, Node<T> *next):data(data), next(next) {}
template<typename T>
Node<T>::Node() {}

#endif //MYTREE_NODE_H
