#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include "Assistance.h"
using namespace std;

// �����
template<class ElemType>
struct Node {
// ���ݳ�Ա:
    ElemType data;                // ������
    Node<ElemType> *next;        // ָ����

// ���캯��:
    Node();                        // �޲����Ĺ��캯��
    Node(ElemType item, Node<ElemType> *link = NULL);    // ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ����Ϊ�յĽ��
{
    next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
    data = item;
    next = link;
}

#endif
