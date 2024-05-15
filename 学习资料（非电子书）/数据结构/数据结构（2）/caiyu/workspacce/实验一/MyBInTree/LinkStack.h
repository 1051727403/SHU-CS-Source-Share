#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// 结点类
#include "Assistance.h"
// 链栈类
template<class ElemType>
class LinkStack
{
protected:
//  链栈的数据成员:
    Node<ElemType> *top;							// 栈顶指针

public:
//  链栈的函数成员:
    LinkStack();									// 无参数的构造函数
    virtual ~LinkStack();							// 析构函数
    int GetLength() const;							// 求栈长度
    bool IsEmpty() const;							// 判断栈是否为空
    void Clear();									// 将栈清空
    void Traverse(void (*Visit)(const ElemType &)) const ;	// 遍历栈
    Status Push(const ElemType e);					// 入栈
    Status Top(ElemType &e) const;					// 返回栈顶元素
    Status Pop(ElemType &e);						// 出栈
    LinkStack(const LinkStack<ElemType> &s);		// 复制构造函数
    LinkStack<ElemType> &operator =(const LinkStack<ElemType> &s); // 赋值语句重载
};


// 链栈类的实现部分
template<class ElemType>
LinkStack<ElemType>::LinkStack()
// 操作结果：构造一个空栈表
{
    top = NULL;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// 操作结果：销毁栈
{
    Clear();
}

template <class ElemType>
int LinkStack<ElemType>::GetLength() const
// 操作结果：返回栈元素个数
{
    int count = 0;		// 计数器
    Node<ElemType> *p;
    for (p = top; p != NULL; p = p->next)		// 用p依次搜寻每个元素
        count++;		// 统计链栈中结点数
    return count;
}

template<class ElemType>
bool LinkStack<ElemType>::IsEmpty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
    return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// 操作结果：清空栈
{
    Node<ElemType> *p;
    while (top != NULL) {
        p = top;
        top = top->next;
        delete p;
    }
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：从栈顶到栈底依次对栈的每个元素调用函数(*visit)访问
{
    Node<ElemType> *p;
    for (p = top; p != NULL; p = p->next)	// 用p依次搜寻当前栈的每个元素
        (*Visit)(p->data);		// 对p所指向的元素调用函数(*visit)访问
}

template<class ElemType>
Status LinkStack<ElemType>::Push(const ElemType e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,否则如动态内存已耗尽
//	将返回OVER_FLOW
{
    Node<ElemType> *p = new Node<ElemType>(e, top);
    if (p == NULL) 	// 系统内存耗尽
        return OVER_FLOW;
    else	{	// 操作成功
        top = p;
        return SUCCESS;
    }
}

template<class ElemType>
Status LinkStack<ElemType>::Top(ElemType &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
    if(IsEmpty())	// 栈空
        return UNDER_FLOW;
    else	{	// 栈非空,操作成功
        e = top->data;				// 用e返回栈顶元素
        return SUCCESS;
    }
}

template<class ElemType>
Status LinkStack<ElemType>::Pop(ElemType &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
{
    if (IsEmpty())	// 栈空
        return UNDER_FLOW;
    else	{	// 操作成功
        Node<ElemType> *p = top;	// 保留原栈顶
        e = top->data;				// 用e返回栈顶元素
        top = top->next;			// 修改栈顶
        delete p;					// 删除原栈顶结点
        return SUCCESS;
    }
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &s)
// 操作结果：由栈s构造新栈--复制构造函数
{
    if (s.IsEmpty())	// s为空
        top = NULL;									// 构造一空栈
    else 	{	                                    // s非空,复制栈
        top = new Node<ElemType>(s.top->data);	// 生成当前栈项
        Node<ElemType> *q = top;			        // 设置当前栈底指针
        for (Node<ElemType> *p = s.top->next; p != NULL; p = p->next){
            q->next = new Node<ElemType>(p->data); // 向栈底追加元素
            q = q->next;					       // 修改栈底指针
        }
    }
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &s)
// 操作结果：将栈s赋值给当前栈--赋值语句重载
{
    if (&s != this)	{
        Clear();			// 清空当前栈
        if (!s.IsEmpty())	{	                            // s非空,复制栈
            top = new Node<ElemType>(s.top->data);       // 生成当前栈项
            Node<ElemType> *q = top;			            // 设置当前栈底指针
            for (Node<ElemType> *p = s.top->next; p != NULL; p = p->next){
                q->next = new Node<ElemType>(p->data);      // 向栈底追加元素
                q = q->next;			                    // 修改栈底指针
            }
        }
    }
    return *this;
}

#endif
