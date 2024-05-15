#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "Node.h"				// 结点类
#include "Assistance.h"
// 链队列类

template<class ElemType>
class LinkQueue
{
protected:
//  链队列实现的数据成员:
    Node<ElemType> *front, *rear;					// 队头队尾指指

public:
    LinkQueue();									// 无参数的构造函数
    virtual ~LinkQueue();							// 析构函数
    int GetLength() const;								// 求队列长度
    bool IsEmpty() const;								// 判断队列是否为空
    void Clear();									// 将队列清空
    void Traverse(void (*Visit)(const ElemType &)) const ;	// 遍历队列
    Status DelQueue(ElemType &e);				     // 出队操作
    Status GetHead(ElemType &e) const;			     // 取队头操作
    Status EnQueue(const ElemType e);			     // 入队操作
    LinkQueue(const LinkQueue<ElemType> &copy);		// 复制构造函数
    LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// 赋值语句重载
};

// 链队列类的实现部分

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// 操作结果：构造一个空队列
{
    rear = front = new Node<ElemType>;	// 生成链队列头结点
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// 操作结果：销毁队列
{
    Clear();
    delete front;
}

template<class ElemType>
int LinkQueue<ElemType>::GetLength() const
// 操作结果：返回队列长度
{
    int count = 0;		// 初始化计数器
    for (Node<ElemType> *p = front->next; p != NULL; p = p->next)
        count++;		// 统计链队列中的结点数
    return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::IsEmpty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
    return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear()
// 操作结果：清空队列
{
    Node<ElemType> *p = front->next;
    while (p != NULL)	{	// 依次删除队列中的元素结点
        front->next = p->next;
        delete p;
        p = front->next;
    }
    rear = front;
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
    for (Node<ElemType> *p = front->next; p != NULL; p = p->next)
        // 对队列每个元素调用函数(*visit)访问
        (*Visit)(p->data);
}


template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
    if (!IsEmpty()) 	{	// 队列非空
        Node<ElemType> *p = front->next;	// 指向队列头素
        e = p->data;						// 用e返回队头元素
        front->next = p->next;				// front指向下一元素
        if (rear == p)	// 出队前队列中只有一个元素，出队后为空队列
            rear = front;
        delete p;							// 释放出队的元素结点
        return SUCCESS;
    }
    else
        return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
    if (!IsEmpty()) 	{	            // 队列非空
        e = front->next->data;		// 用e返回队头元素
        return SUCCESS;
    }
    else
        return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType e)
// 操作结果：如果系统空间不够，返回OVER_FLOW,
//	否则插入元素e为新的队尾，返回SUCCESS
{
    Node<ElemType> *p;
    p = new Node<ElemType>(e);	        // 生成一个新结点
    if (p) {
        rear->next = p;	                // 将新结点加在队尾
        rear = rear->next;				// rear指向新队尾
        return SUCCESS;
    }
    else                               //系统空间不够，返回OVER_FLOW
        return OVER_FLOW;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// 操作结果：由队列copy构造新队列--复制构造函数
{
    rear = front = new Node<ElemType>;	// 生成队列头结点
    for (Node<ElemType> *p = copy.front->next; p != NULL; p = p->next)
        // 取copy队列每个元素的值,将其在当前队列中作入队列操作
        EnQueue(p->data);
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// 操作结果：将队列copy赋值给当前队列--赋值语句重载
{
    if (&copy != this)	{
        Clear();       //清除原有队列
        for (Node<ElemType> *p = copy.front->next; p != NULL; p = p->next)
            // 取copy队列每个元素的值,将其在当前队列中作入队列操作
            EnQueue(p->data);
    }
    return *this;
}

#endif
