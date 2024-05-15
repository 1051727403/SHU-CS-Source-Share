#ifndef __CHILD_SIBLING_FOREST_NODE_H__
#define __CHILD_SIBLING_FOREST_NODE_H__

#include <iostream>

using namespace std;
// �����ֵܱ�ʾ�������
template<class ElemType>
struct ChildSiblingTreeNode {
// ���ݳ�Ա:
    ElemType data;                                // ������
    ChildSiblingTreeNode<ElemType> *firstChild;    // ָ���׺���ָ����
    ChildSiblingTreeNode<ElemType> *nextSibling;// ָ�����ֵ�ָ����

// ���캯��:
    ChildSiblingTreeNode();                        // �޲����Ĺ��캯��
    ChildSiblingTreeNode(ElemType val,            // �в����Ĺ��캯��
                         ChildSiblingTreeNode<ElemType> *fChild = NULL,
                         ChildSiblingTreeNode<ElemType> *nSibling = NULL);

};

// �����ֵܱ�ʾ��������ʵ�ֲ���
template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode()
// �������������ָ����Ϊ�յĽ��
{
    firstChild = nextSibling = NULL;
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType val,
                                                     ChildSiblingTreeNode<ElemType> *fChild,
                                                     ChildSiblingTreeNode<ElemType> *nSibling)
// �������������һ��������Ϊval���׺���ΪfChild����һ�ֵ�ΪnChild�Ľ��
{
    data = val;
    firstChild = fChild;
    nextSibling = nSibling;
}

#endif
