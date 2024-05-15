#include <iostream>
#include "ChildSiblingTree.h"

int main() {
    char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
    int n = 8;
    ChildSiblingTree<char> t(items, parents, n);
    DisplayTWithConcaveShape(t);
    cout << "======================================================================" << endl << endl;

    char items1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int parents1[] = {-1, 0, 0, 0, 1, 1, 3, 3, 7};
    int n1 = 9;
    ChildSiblingTree<char> t1(items1, parents1, n1);

    cout << t1.myHeight(t1.GetRoot());
    cout << t1.myHeight2(t1.GetRoot());

    cout << t.myDegree(t.GetRoot());

    cout << t1.getWidth(t1.GetRoot());

    t1.getLeaves(t1.GetRoot());
    cout << count;
    cout << t1.getLeaves2(t1.GetRoot());
}
