#include <iostream>
#include "Assistance.h"
#include "BinaryTree.h"

int main() {
    char pre[] = {'A', 'B', 'D', 'E', 'G', 'H', 'C', 'F', 'I'}; // 先序序列
    char in[] = {'D', 'B', 'G', 'E', 'H', 'A', 'C', 'F', 'I'};  // 中序序列
    int n = 9;                                          // 结点个数
    BinaryTree<char> preInbt;
    preInbt = CreateBinaryTree(pre, in, n);           // 构造二叉树

    cout << "pre[]={'A','B','D','E','G','H','C','F','I'}" << endl;
    cout << "in[]={'D','B','G','E','H','A','C','F','I'}" << endl;
    DisplayBTWithTreeShape<char>(preInbt);
    cout << endl;

    cout
            << "========================================================================================================="
            << endl << endl << endl;
//    preInbt.myPreOrder(preInbt.GetRoot());
//    preInbt.myInOrder(preInbt.GetRoot());
//    preInbt.myPostOrder(preInbt.GetRoot());
//    cout << endl;
//    preInbt.myPreOrderStack(preInbt.GetRoot());
//    preInbt.myInOrderStack(preInbt.GetRoot());
//    preInbt.myLevelOrder(preInbt.GetRoot());
//    int count = 0;
//    cout << preInbt.myNodeCount2(preInbt.GetRoot());
//    cout << preInbt.myHeight(preInbt.GetRoot());
//    cout << preInbt.getLeavesCount(preInbt.GetRoot());
//    cout << preInbt.get1NodeCount(preInbt.GetRoot()) << endl;
//    cout << preInbt.get1NodeCountway2(preInbt.GetRoot()) << endl;
//    cout << preInbt.get2NodeCount(preInbt.GetRoot()) << endl;
//    preInbt.myLevelOrderReverse(preInbt.GetRoot());


//    char pre1[] = {'A', 'B', 'C', 'D'}; // 先序序列
//    char in1[] = {'B', 'A', 'C', 'D'};  // 中序序列
//    int n1 = 4;                                          // 结点个数
//    char pre1[] = {'A', 'B'}; // 先序序列
//    char in1[] = {'B', 'A'};  // 中序序列
//    int n1 = 2;                                          // 结点个数
//    BinaryTree<char> preInbt1;
//    preInbt1 = CreateBinaryTree(pre1, in1, n1);           // 构造二叉树

//    cout << preInbt1.isComplete(preInbt1.GetRoot());

//    preInbt.myPostOrderStack(preInbt.GetRoot());
//    cout << preInbt.HeightQueue(preInbt.GetRoot());
//    cout << preInbt.isComplete(preInbt.GetRoot());
//    preInbt.searchAllAncestor(preInbt.GetRoot(), 'I');

    cout << preInbt.WeightQueue(preInbt.GetRoot());
}



