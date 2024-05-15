#ifndef __CHILD_SIBLING_FOREST_NODE_H__
#define __CHILD_SIBLING_FOREST_NODE_H__

#include <iostream>

using namespace std;
// 孩子兄弟表示树结点类
template<class ElemType>
struct ChildSiblingTreeNode {
// 数据成员:
    ElemType data;                                // 数据域
    ChildSiblingTreeNode<ElemType> *firstChild;    // 指向首孩子指针域
    ChildSiblingTreeNode<ElemType> *nextSibling;// 指向右兄弟指针域

// 构造函数:
    ChildSiblingTreeNode();                        // 无参数的构造函数
    ChildSiblingTreeNode(ElemType val,            // 有参数的构造函数
                         ChildSiblingTreeNode<ElemType> *fChild = NULL,
                         ChildSiblingTreeNode<ElemType> *nSibling = NULL);

};

// 孩子兄弟表示树结点类的实现部分
template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode()
// 操作结果：构造指针域为空的结点
{
    firstChild = nextSibling = NULL;
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType val,
                                                     ChildSiblingTreeNode<ElemType> *fChild,
                                                     ChildSiblingTreeNode<ElemType> *nSibling)
// 操作结果：构造一个数据域为val、首孩子为fChild、下一兄弟为nChild的结点
{
    data = val;
    firstChild = fChild;
    nextSibling = nSibling;
}

#endif
