#ifndef __CHILD_SIBLING_TREE_H__
#define __CHILD_SIBLING_TREE_H__

#include "LinkQueue.h"                        // 链队列
#include "ChildSiblingTreeNode.h"        // 孩子兄弟表示树结点类

// 孩子兄弟表示树类
template<class ElemType>
class ChildSiblingTree {
protected:
//  树的数据成员:
    ChildSiblingTreeNode<ElemType> *root;            // 根指针

//	辅助函数:
    void Destroy(ChildSiblingTreeNode<ElemType> *&r);        // 销毁以r为根的树
    void PreRootOrder(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
    // 先根遍历以r为根的数
    void PostRootOrder(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
    // 后根遍历以r为根的数
    int NodeCount(ChildSiblingTreeNode<ElemType> *r) const;    // 求以r为根的树的结点个数
    // 求以r为根的树的高
    int Degree(ChildSiblingTreeNode<ElemType> *r) const;    // 求以r为根的树的度
//	void Delete(ChildSiblingTreeNode<ElemType> *r);		// 删除以r为根的树
    ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *r,
                                           const ChildSiblingTreeNode<ElemType> *cur) const;    //  求cur的双亲
    ChildSiblingTreeNode<ElemType> *CopyTree(ChildSiblingTreeNode<ElemType> *copy);
    // 复制树
    ChildSiblingTreeNode<ElemType> *CreateTreeGhelp(ElemType items[], int parents[], int r, int n);
    // 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树，并 求树的根

public:
//  孩子兄弟表示树类方法的声明:
    ChildSiblingTree();                                    // 无参数的构造函数
    virtual ~ChildSiblingTree();                        // 析构函数
    ChildSiblingTreeNode<ElemType> *GetRoot() const;    //  求树的根
    bool IsEmpty() const;                                // 判断树是否为空
    Status GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
    // 用e 求结点元素值
    Status SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
    // 将结cur的值置为e
    void PreRootOrder(void (*Visit)(const ElemType &)) const;        // 树的先根序遍历
    void PostRootOrder(void (*Visit)(const ElemType &)) const;        // 树的后根序遍历
    void LevelOrder(void (*Visit)(const ElemType &)) const;            // 树的层次遍历
    int NodeCount() const;                                            // 求树的结点个数
    int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;        // 求结点cur的度
    int Degree() const;                                                // 求树的度
    ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;
    // 求树结点cur的第一个孩子
    ChildSiblingTreeNode<ElemType> *NextSibling(ChildSiblingTreeNode<ElemType> *cur) const;
    // 求树结点cur的下一个兄弟
    ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *cur) const;
    // 求结点cur的双亲
    Status InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);
    // 将数据元素e插入为cur的第i个孩子
    Status DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);// 删除cur的第i个棵子树
    int Height() const;                                    //  求树的高
    ChildSiblingTree(const ElemType &e);                // 建立以数据元素e为根的树
    ChildSiblingTree(const ChildSiblingTree<ElemType> &copy);    // 复制构造函数
    ChildSiblingTree(ElemType items[], int parents[], int n);
    // 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
    ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r);// 建立以r为根的树
    ChildSiblingTree<ElemType> &operator=(const ChildSiblingTree<ElemType> &copy);
    // 重载赋值运算


    void myPreRootOrder(ChildSiblingTreeNode<ElemType> *r);
    void myPreRootOrder2(ChildSiblingTreeNode<ElemType> *r);

    void myLevelOrder(ChildSiblingTreeNode<ElemType> *r);

    int myHeight(ChildSiblingTreeNode<ElemType> *r);
    int myHeight2(ChildSiblingTreeNode<ElemType> *r);

    int Height(ChildSiblingTreeNode<ElemType> *r) const;

    int myDegree(ChildSiblingTreeNode<ElemType> *r);

    int getLeaves(ChildSiblingTreeNode<ElemType> *r);

    int getLeaves2(ChildSiblingTreeNode<ElemType> *r);

    int getWidth(ChildSiblingTreeNode<ElemType> *r);
};

template<class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
// 按凹入表示法显示树，level为层次数，设根结点的层次数为1
template<class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t);
// 按凹入表示法显示树

// 孩子兄弟表示树类的实现部分

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
// 操作结果：构造一个空树
{
    root = NULL;                    // 表示树为空
}

template<class ElemType>
void ChildSiblingTree<ElemType>::Destroy(ChildSiblingTreeNode<ElemType> *&r)
// 操作结果：销毁以r为根的树
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r != NULL) {
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            Destroy(p);        // 销毁子树
        delete r;                // 销毁根结点
        r = NULL;
    }
}

template<class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
// 操作结果：销毁树--析造函数
{
    Destroy(root);
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::GetRoot() const
// 操作结果： 求树的根
{
    return root;
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::IsEmpty() const
// 操作结果：判断树是否为空
{
    return root == NULL;
}

template<class ElemType>
Status ChildSiblingTree<ElemType>::GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
// 操作结果：用e 求结点cur元素值,如果不存在结点cur,函数 求NOT_PRESENT,否则 求ENTRY_FOUND
{
    if (cur == NULL)
        return NOT_PRESENT;
    else {
        e = cur->data;            // 用e 求元素值
        return ENTRY_FOUND;        //  求ENTRY_FOUND
    }
}

template<class ElemType>
Status ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则 求FAIL,否则 求SUCCESS,并将结点cur的值设置为e
{
    if (cur == NULL)
        return FAIL;
    else {
        cur->data = e;            // 将结点cur的值设置为e
        return SUCCESS;            //  求SUCCESS
    }
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(ChildSiblingTreeNode<ElemType> *r,
                                              void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对以r为根的树的每个元素调用函数(*visit)访问 
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r != NULL) {
        (*Visit)(r->data);            // 访问根结点
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            PreRootOrder(p, Visit);// 依次先根序遍历根结点的每棵子树
    }
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对树的每个元素调用函数(*visit)访问 
{
    PreRootOrder(GetRoot(), Visit);
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(ChildSiblingTreeNode<ElemType> *r,
                                               void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对以r为根的树的每个元素调用函数(*visit)访问
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r != NULL) {
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            PostRootOrder(p, Visit);    // 依次后根序遍历每棵子树
        (*Visit)(r->data);                    // 访问根结点
    }
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对树的每个元素调用函数(*visit)访问
{
    PostRootOrder(GetRoot(), Visit);
}

template<class ElemType>
void ChildSiblingTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历树
{
    LinkQueue<ChildSiblingTreeNode<ElemType> *> q;    // 定义队列对象
    ChildSiblingTreeNode<ElemType> *cur, *p;

    if (root != NULL) q.EnQueue(root);               // 如果根非空,则根结点指针入队列
    while (!q.IsEmpty()) {
        q.DelQueue(cur);                           //  队头结点出队为当前结点cur
        (*Visit)(cur->data);                       // 访问当前结点cur
        for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
            q.EnQueue(p);                           // 依次将cur的孩子结点指针入队列
    }
}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeCount(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果： 求以r为根的树的结点个数
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r == NULL) return 0;            // 空树结点个数为0
    else {
        int subTreeNodeCountSum = 0;
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            subTreeNodeCountSum += NodeCount(p);// 累加子树结点个数
        return 1 + subTreeNodeCountSum;       // 非空树结点个为子树的结点个数之和再加1
    }
}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeCount() const
// 操作结果： 求树的结点个数
{
    return NodeCount(root);
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Height(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果： 求以r为根的树的高
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r == NULL)
        return 0;
    else {
        int maxSubTreeHeight = 0, h;
        for (p = FirstChild(r); p != NULL; p = NextSibling(p)) {
            h = Height(p);            // 求各子树的高
            maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
            // 求各子树高的最大值
        }
        return maxSubTreeHeight + 1;    // 树高为各子树的最大值再加1
    }
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Height() const
// 操作结果： 求树的高
{
    return Height(root);
}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果： 求结点cur的度
{
    ChildSiblingTreeNode<ElemType> *p;
    int count = 0;
    for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
        count++;                    // 对孩子个数进行计数
    return count;
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Degree(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果： 求以r为根的树的度
{
    ChildSiblingTreeNode<ElemType> *p;
    int d = 0;
    int maxSubTreeDegree = 0;    // 子树度的最大度
    for (p = FirstChild(r); p != NULL; p = NextSibling(p)) {
        d++;                    // 对孩子个数进行计数
        int subTreeDegree = Degree(p);    //  求以p为根的子树度
        maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
        // 求子树度最大值
    }
    return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
// 操作结果： 求树的度
{
    return Degree(root);
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如cur无孩子,则返回NULL,否则返回树结点cur的第一个孩子,
{
    if (cur == NULL)
        return NULL;                // 空结点无孩子
    else
        return cur->firstChild;        // firstChild为第一个孩子
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::NextSibling(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如果结点cur为空或没有下一个兄弟,则返回NULL,否则返回cur的下一个兄弟
{
    if (cur == NULL)
        return NULL;                // 空结点右兄弟
    else
        return cur->nextSibling;    // nextSibling为下一个兄弟
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *r,
                                                                   const ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：求以r为根的树, 结点cur的双亲
{
    if (r == NULL) return NULL;                // 空二叉树

    ChildSiblingTreeNode<ElemType> *p;        // 孩子
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p == cur) return r;                // cur是r的孩子

    for (p = FirstChild(r); p != NULL; p = NextSibling(p)) {
        ChildSiblingTreeNode<ElemType> *q;
        q = Parent(p, cur);                    // 在子树上求cur的双亲
        if (q != NULL) return q;            // 双亲在子树上
    }

    return NULL;                            // 未找到双亲
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：求结点cur的双亲
{
    return Parent(root, cur);
}

template<class ElemType>
Status ChildSiblingTree<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
    if (cur == NULL) return FAIL;
    if (i < 1 || i > NodeDegree(cur) + 1) return FAIL;

    ChildSiblingTreeNode<ElemType> *newNode = new ChildSiblingTreeNode<ElemType>(e);
    // 申请新结点空间
    if (i == 1) {
        newNode->nextSibling = cur->firstChild;
        cur->firstChild = newNode;                // newNode插入为cur的第一个孩子
    } else {
        ChildSiblingTreeNode<ElemType> *p = FirstChild(cur);// 取cur的孩子
        for (int k = 1; k < i - 1; k++)
            p = NextSibling(p);       // 求插入位置的前一个兄弟p
        newNode->nextSibling = p->nextSibling;
        p->nextSibling = newNode;
    }
    return SUCCESS;
}

/*
template <class ElemType>
void ChildSiblingTree<ElemType>::Delete(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：删除以r为根的树
{
	if (r != NULL)	{	// r非空
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = NextSibling(child))
		{	// 找查r的子树
			Delete(child);						// 删除以child为根的子树
		}
		delete r;									// 释放r
		r = NULL;
	}
}
*/
template<class ElemType>
Status ChildSiblingTree<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// 操作结果：删除cur的第i个棵子树,如果删除成功,则 求SUCCESS,否则 求FAIL
{
    ChildSiblingTreeNode<ElemType> *p, *q;

    if (i < 0 && i > NodeDegree(cur)) return FAIL;    // 子树位置不正确，操作失败

    if (i == 1) {
        p = cur->firstChild;
        cur->firstChild = p->nextSibling;        // 删除cur的第1棵子树
    } else {
        q = FirstChild(cur);
        for (int n = 1; n < i - 1; n++)
            q = NextSibling(q);            // 查找cur的第i - 1个孩子
        p = q->nextSibling;
        q->nextSibling = p->nextSibling;        // 删除第i个棵子树
    }
    Destroy(p);                                    // 销毁第i棵子树
    return SUCCESS;                                // 返回操作成功
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType &e)
// 操作结果：建立以数据元素e为根的树
{
    root = new ChildSiblingTreeNode<ElemType>(e);    // 生成根结点
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CopyTree(ChildSiblingTreeNode<ElemType> *troot)
// 操作结果：将以troot为根的树复制成新的树, 求新树的根
{
    if (troot == NULL)
        return NULL;                    // 空二叉树根为空
    else {    // 复制非空二叉树
        ChildSiblingTreeNode<ElemType> *r = new ChildSiblingTreeNode<ElemType>(troot->data);    // 复制根结点
        ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur, *p;
        for (p = FirstChild(troot); p != NULL; p = NextSibling(p)) {    // 复制子树
            subTreeRoot = CopyTree(p);    // 复制子树
            if (r->firstChild == NULL) {
                r->firstChild = subTreeRoot;    // subTreeRoot为首孩子
                cur = subTreeRoot;                // cur最新复制的子树的根
            } else {
                cur->nextSibling = subTreeRoot;// subTreeRoot为下一个兄弟
                cur = subTreeRoot;                // cur最新复制的子树的根
            }
        }
        return r;
    }
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ChildSiblingTree<ElemType> &t)
// 操作结果：由已知树构造新树——复制构造函数
{
    root = CopyTree(t.GetRoot());
}

template<class ElemType>
ChildSiblingTreeNode<ElemType> *
ChildSiblingTree<ElemType>::CreateTreeGhelp(ElemType elems[], int parents[], int r, int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树，并返回树的根
{
    if (r >= 0 && r < n) {
        ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(elems[r]);    // 复制根结点
        ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;
        for (int i = 0; i < n; i++) {    // 查找r的孩子
            if (parents[i] == r) {    // 建立以pos为根的子树
                subTreeRoot = CreateTreeGhelp(elems, parents, i, n);
                if (rt->firstChild == NULL) {    // subTreeRoot为rt第一棵子树的根
                    rt->firstChild = subTreeRoot;
                    cur = subTreeRoot;            // cur最新复制的子树的根
                } else {                   // subTreeRoot为cur的下一个兄弟
                    cur->nextSibling = subTreeRoot;
                    cur = subTreeRoot;
                }
            }
        }
        return rt;
    } else return NULL;                                    // r非法，建立空树
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ElemType elems[], int parents[], int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为0,结点个数为n的树
{
    root = CreateTreeGhelp(elems, parents, 0, n);    // 用辅助函数建立树
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：建立以r为根的树
{
    root = r;
}

template<class ElemType>
ChildSiblingTree<ElemType> &ChildSiblingTree<ElemType>::operator=(const ChildSiblingTree<ElemType> &copy)
// 操作结果：由已知树copy复制到当前树--赋值运算重载
{
    if (&copy != this) {
        Destroy(root);                        // 销毁树
        root = CopyTree(copy.GetRoot());
    }
    return *this;
}
template<class ElemType>
void
ChildSiblingTree<ElemType>::myPreRootOrder(ChildSiblingTreeNode<ElemType> *r) {
    if (r == NULL)
        return;
//    ChildSiblingTreeNode<ElemType> *p;
    cout << r->data;
    for (r = FirstChild(r); r != NULL; r = NextSibling(r))
        myPreRootOrder(r);
}
template<class ElemType>
void ChildSiblingTree<ElemType>::myPreRootOrder2(ChildSiblingTreeNode<ElemType> *r) {
    if (r == NULL)
        return;
    cout << r->data;
    myPreRootOrder2(r->firstChild);
    myPreRootOrder2(r->nextSibling);
}
template<class ElemType>
int ChildSiblingTree<ElemType>::myHeight(ChildSiblingTreeNode<ElemType> *r) {
    if (r == NULL)
        return 0;
    return max(myHeight(r->firstChild) + 1, myHeight(r->nextSibling));
}
template<class ElemType>
void ChildSiblingTree<ElemType>::myLevelOrder(ChildSiblingTreeNode<ElemType> *r) {
    LinkQueue<ChildSiblingTreeNode<ElemType> *> linkQueue;
    if (r != NULL)
        linkQueue.EnQueue(r);
    while (!linkQueue.IsEmpty()) {
        linkQueue.DelQueue(r);
        cout << r->data;
        for (r = r->firstChild; r != NULL; r = r->nextSibling)
            linkQueue.EnQueue(r);
    }
}
template<class ElemType>
int ChildSiblingTree<ElemType>::myDegree(ChildSiblingTreeNode<ElemType> *r) {
    LinkQueue<ChildSiblingTreeNode<ElemType> *> linkQueue;
    int max_degree = 0, degree = 0;
    if (r != NULL)
        linkQueue.EnQueue(r);
    while (!linkQueue.IsEmpty()) {
        linkQueue.DelQueue(r);
        for (r = r->firstChild; r != NULL; r = r->nextSibling) {
            linkQueue.EnQueue(r);
            degree++;
        }
        max_degree = max(max_degree, degree);
        degree = 0;
    }
    return max_degree;
}
template<class ElemType>
int ChildSiblingTree<ElemType>::myHeight2(ChildSiblingTreeNode<ElemType> *r) {
    LinkQueue<ChildSiblingTreeNode<ElemType> *> linkQueue;
    ChildSiblingTreeNode<ElemType> *tail = r; // tail为本层最后一个
    ChildSiblingTreeNode<ElemType> *last;
    ChildSiblingTreeNode<ElemType> *p;
    int level = 0;
    if (r != NULL) {
        linkQueue.EnQueue(r);
    }
    while (!linkQueue.IsEmpty()) {
        linkQueue.DelQueue(r);
        for (p = r->firstChild; p != NULL; p = p->nextSibling) {
            linkQueue.EnQueue(p);
            last = p;
        }
        if (r == tail) {
            level++;
            tail = last;
        }
    }
    return level;
}
static int count = 0;
template<class ElemType>
int ChildSiblingTree<ElemType>::getLeaves(ChildSiblingTreeNode<ElemType> *r) {
    if (r != NULL) {
        if (r->firstChild == NULL)
            count++;
        for (r = r->firstChild; r != NULL; r = r->nextSibling) {
            getLeaves(r);
        }
    }
}
template<class ElemType>
int ChildSiblingTree<ElemType>::getLeaves2(ChildSiblingTreeNode<ElemType> *r) {
    if (r == NULL)
        return 0;
    if (r->firstChild == NULL)
        return 1 + getLeaves2(r->nextSibling);
    return getLeaves2(r->firstChild) + getLeaves2(r->nextSibling);
}
template<class ElemType>
int ChildSiblingTree<ElemType>::getWidth(ChildSiblingTreeNode<ElemType> *r) {
    LinkQueue<ChildSiblingTreeNode<ElemType> *> linkQueue;
    int max_width = 0;
    if (r != NULL)
        linkQueue.EnQueue(r);
    while (!linkQueue.IsEmpty()) {
        int width = linkQueue.GetLength();
        max_width = max(width, max_width);
        for (int i = 0; i < width; i++) {
            linkQueue.DelQueue(r);
            for (r = r->firstChild; r != NULL; r = r->nextSibling)
                linkQueue.EnQueue(r);
        }
    }
    return max_width;
}

template<class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t,
                              ChildSiblingTreeNode<ElemType> *r, int level)
// 操作结果：按凹入表示法显示树，level为层次数，设根结点的层次数为1
{
    ChildSiblingTreeNode<ElemType> *p;
    if (r != NULL) {
        cout << endl;                                    //显示新行
        for (int i = 0; i < level - 1; i++)
            cout << " ";                                //确保在第level列显示结点
        ElemType e;
        t.GetElem(r, e);                            // 取出结点r的元素值
        cout << e;                                    // 显示结点元素值
        for (p = t.FirstChild(r); p != NULL; p = t.NextSibling(p))
            DisplayTWithConcaveShape(t, p, level + 1);// 依次显示各棵子树
    }
}

template<class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t)
// 操作结果：按凹入表示法显示树
{
    DisplayTWithConcaveShape(t, t.GetRoot(), 1);// 调用辅助函数实现按凹入表示法显示树
    cout << endl;                                    // 换行
}

#endif
