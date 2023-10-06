// LinkList.h		����������ģ��	20200828 By LiQing ����ָ����
#ifndef LINKLIST_H
#define LINKLIST_H
#define _CRT_SECURE_NO_WARNINGS			// for VS2019
#pragma warning( disable : 4290 )		// for VS2019
#pragma warning( disable : 4996 )		// for VS2019
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

template <typename T> class LinkList;	// ����㣺�����ࣨģ�壩��ǰ����

template <typename T> class Node		// �м�㣺����ࣨģ�壩
{
public:
	Node() : next(NULL) {}										// Ĭ�ϵĹ��캯�������ⲻ��ʼ��data�Ա���data�ġ�ԭ��̬��
	Node(const T& t) : data(t), next(NULL) {}					// ת�����캯��
	Node(const Node<T>& node) : data(node.data), next(NULL) {}	// �������캯��
	Node<T>& operator=(const Node<T>& node)					// ���ظ�ֵ���������
	{
		data = node.data;				// ���丳ֵʱ�����ı������򣬲��ı����ӷ�ʽ
		return *this;
	}
	friend class LinkList<T>;			// �������࣬��ʹLinkList<T>��ĳ�Ա�������ʽ�����˽�г�Աdata��next
private:
	T data;								// ����㣺��������ʽ�������ͣ�
	Node<T>* next;						// ָ����
};

template <typename T> class LinkList			// ����������ģ�����
{
public:
	LinkList(int n = 0, const T* array = NULL);		// ���캯������Ĭ�ϵĹ��캯����ת�����캯���ȣ�
	LinkList(const LinkList& list);				// (��)�������캯��
	~LinkList();								// ��������
	LinkList& operator=(const LinkList& list);	// (��)��ֵ���������

	void PutList(ostream& out) const;			// ����������н������ݵ�����out���󶨵�ostream���󣬸ö��������cout��Ҳ�������ļ�����
	void GetList(istream& in);					// �������豸in��ȡ���ݣ��γ�����
	int Save(const char* filename);				// ���������н�������д��ָ���ļ�
	int Load(const char* filename);				// ��ָ���ļ��ж�ȡ���ݣ���������
	void ShowList() const;						// ����������н������ݣ���һ�ָ�ʽ����һ���������
	void ShowList1() const;

	Node<T>* Insert(const T& t);				// ����һ������Ϊ�µ��׽��
	Node<T>* InsertBefore(const T& t);			// �ڵ�ǰ���֮ǰ����һ�����
	Node<T>* InsertAfter(const T& t);			// �ڵ�ǰ���֮�����һ�����
	Node<T>* Append(const T& t);				// ׷��һ������Ϊ�µ�β���

	void FreeList();							// �ͷ������е����н��
	T DeleteCurNode() throw(int);				// ɾ����ǰ��㣬����һ����㣨��Ϊ�µĵ�ǰ��㣩��ֵ���ر�ɾ�����������ֵ
	T ModifyData(const T& t) throw(int);		// �޸�(�滻)��ǰ������������ֵ

	int NumNodes() const;						// ���ؽ����
	int CurPos() const;							// ���ص�ǰ������ţ�-1��ʾ�޵�ǰ��㣩
	Node<T>* CurNode();							// ���ص�ǰ���ĵ�ַ��NULL��ʾ�޵�ǰ��㣩
	T& CurData() throw(int);					// ���÷��ص�ǰ����������Ա���������ñ��ʽ������ֵ

	Node<T>* GoTop(), * Go(int n), * GoBottom();	// ��ǰ�����Զ�λ���׽�㡢��n�����(n��0��)��β���
	Node<T>* Skip(int n = 1)  throw(int);			// ��ǰ�����Զ�λ��n��Ϊ��������Ĭ��nΪ1��ʾ��һ�����
	template <typename TYPE> Node<T>* Locate(const TYPE& x, bool newsearch = false); // ��ǰ���������������TYPE���ͣ���λ

	template <typename TYPE> void Sort(const TYPE& x, bool ascending = true);	// ����TYPE���������������
	void Reverse();								// �����㵹��

private:
	Node<T>* head, * cur_node;					// �����׽���ַ��ָ�룩����ǰ����ַ��ָ�룩
	int num;									// ���ڼ�¼�����н��ĸ���
};

/********************************************************************
 * ��ģ���Ա��������������Ӧ�ñ�д��ͷ�ļ��У������ڴ���ɳ�Ա���� *
 ********************************************************************/
template <typename T>
LinkList<T>::LinkList(int n, const T* array) : head(NULL), cur_node(NULL), num(0)	// ���캯������Ĭ�ϵĹ��캯����ת�����캯���ȣ�
{
	Node<T>* p;
	for (int i = n - 1; i >= 0; i--)
	{
		p = new Node<T>;				// �Զ�����Node<T>Ĭ�ϵĹ��캯�������ѽ��
		if (array != NULL)
			p->data = array[i];			// ���arrayΪNULL���򱣳�p->data��Ĭ��״̬
		p->next = head;					// ����ͷ�巨��������Ԫ�ص��򽫶ѽ�����β��뵽�����׽��ǰ
		head = p;
	}
	cur_node = head;
	num = n;
}

template <typename T>
LinkList<T>::LinkList(const LinkList& list) : head(NULL), cur_node(NULL), num(0)	// (��)�������캯��
{
	*this = list;	// ����ͨ����ʽ��ð�Ź��򴴽�һ��������Ȼ�����(��)��ֵ�����������ֵ��������
}

template <typename T>
LinkList<T>::~LinkList()						// ��������
{
	FreeList();
}

template <typename T>
LinkList<T>& LinkList<T>::operator=(const LinkList& list)// (��)��ֵ���������
{
	if (this == &list)					// �����ֵ������ʽ����ֵ�����뱾����Ϊͬһ�������ǵĵ�ַ��ͬ��
		return *this;					// ��ֱ�ӷ��ر�����*this��
	// ��������˫Ŀ���������ʱӦ��ע������⡣�����ֵ���ʽ������������Ϊͬһ����óȻִ���������佫������ش���
	// ��Ϊ�������ұߵĶ���list������Ϊconst���������ͷ�����߶��󣨼������󣩵����н����ұ߶�������н��Ҳ�Ͳ�������
	FreeList();							// ��Ϊ����������ֵ���󣬹ʿ����ͷű���������н�㡣
	Node<T>* temp = NULL;
	for (Node<T>* p = list.head; p != NULL; p = p->next)
	{
		Append(p->data);				// ������ġ���ǰ�������Append�����仯
		if (p == list.cur_node)			// �����������ġ���ǰ�����
			temp = cur_node;			// ��¼�±�����ġ���ǰ�����
	}
	cur_node = temp;
	return *this;
}

template <typename T>
void LinkList<T>::PutList(ostream& out) const	// ����������н������ݵ�����out���󶨵�ostream���󣬸ö��������cout��Ҳ�������ļ�����
{
	out << '(' << num << ')' << endl;			// ����������򱣴����ļ������ĸ���
	for (Node<T>* p = head; p != NULL; p = p->next)
		out << p->data << endl;
}

template <typename T>
void LinkList<T>::GetList(istream& in)			// �������豸in��ȡ���ݣ��γ�����
{
	//	FreeList();
	T x;
	char str[80];
	int n;
	in.getline(str, 80, '(');					// ���Ⱥ���'('�ַ�������ܵ�����ǰ���ַ�
	in.getline(str, 80);						// ��ȡ�ַ�����β
	n = atoi(str);
	for (int i = 0; i < n; i++)
	{
		in >> x;
		Append(x);
	}
	cur_node = head;
	in.clear();
	in.sync();
}

template <typename T>
ostream& operator<<(ostream& out, const LinkList<T>& list)		// ���������ǳ�Ա��������Ϊһ����ͨ��C++����
{
	list.PutList(out);
	return out;
}

template <typename T>
istream& operator>>(istream& in, LinkList<T>& list)			// ���������ǳ�Ա��������Ϊһ����ͨ��C++����
{
	list.GetList(in);
	return in;
}

template <typename T>
int LinkList<T>::Save(const char* filename)		// ���������н�������д��ָ���ļ�
{
	ofstream outfile(filename);
	if (outfile.fail())
		return 0;
	outfile << *this;
	outfile.close();
	return num;
}

template <typename T>
int LinkList<T>::Load(const char* filename)		// ��ָ���ļ��ж�ȡ���ݣ���������
{
	int n = NumNodes();
	ifstream infile(filename);
	if (infile.fail())
		return 0;
	infile >> *this;
	infile.close();
	cur_node = head;
	return num - n;
}

template <typename T>
void LinkList<T>::ShowList() const				// ����������н������ݣ���ʽһ����һ���������
{
	for (Node<T>* p = head; p != NULL; p = p->next)
		cout << p->data;
}

template<typename T>
void LinkList<T>::ShowList1() const				// ����������н������ݣ���ʽһ����һ���������
{
	int i = 0;
	for (Node<T>* p = head; p != NULL; p = p->next, i++)
	{
		cout << "|" << i << "\t|" << p->data;
	}

}

template <typename T>
Node<T>* LinkList<T>::Insert(const T& t)		// ����һ������Ϊ�µ��׽��
{
	Node<T>* p = new Node<T>(t);
	p->next = head;
	head = p;
	num++;
	return cur_node = p;
}

template <typename T>
Node<T>* LinkList<T>::InsertBefore(const T& t)	// �ڵ�ǰ���֮ǰ����һ�����
{
	if (cur_node == NULL || head == NULL)
		return cur_node = NULL;
	Node<T>* p = new Node<T>(t);
	if (cur_node == head)
	{
		p->next = head;
		head = p;
	}
	else
	{
		Skip(-1);
		p->next = cur_node->next;
		cur_node->next = p;
	}
	num++;
	return cur_node = p;
}

template <typename T>
Node<T>* LinkList<T>::InsertAfter(const T& t)	// �ڵ�ǰ���֮�����һ�����
{
	if (cur_node == NULL || head == NULL)
		return cur_node = NULL;
	Node<T>* p = new Node<T>(t);
	p->next = cur_node->next;
	cur_node->next = p;
	num++;
	return cur_node = p;
}

template <typename T>
Node<T>* LinkList<T>::Append(const T& t)		// ׷��һ������Ϊ�µ�β���
{
	Node<T>* p = new Node<T>(t);				// Node<T>��ת�����캯��ʹnextΪNULL
	if (head == NULL)
		head = p;
	else
	{
		for (cur_node = head; cur_node->next != NULL; cur_node = cur_node->next)
			;
		cur_node->next = p;
	}
	num++;
	return cur_node = p;
}

template <typename T>
void LinkList<T>::FreeList()					// �ͷ������е����н��
{
	Node<T>* p;
	while (head != NULL)
	{
		p = head;								// ��ʱ����ԭ���׽���ַ���Ա��ͷ�
		head = head->next;						// ԭ�׽��������ԭ�׽�����һ������Ϊ���׽��
		delete p;								// �����õ����������裺�������н�㶼�Ƕ�̬���
	}
	cur_node = NULL;
	num = 0;
}

template <typename T>
T LinkList<T>::DeleteCurNode() throw(int)		// ɾ����ǰ��㣬����һ����㣨��Ϊ�µĵ�ǰ��㣩��ֵ���ر�ɾ�����������ֵ
{
	if (cur_node == NULL || head == NULL)
		throw - 1;
	Node<T>* p;
	T x;
	if (cur_node == head)
	{
		p = head;
		head = head->next;
		x = p->data;
		delete p;
		cur_node = head;
	}
	else
	{
		Skip(-1);
		p = cur_node->next;			// pָ���ɾ���Ľ��
		cur_node->next = p->next;	// ��ɾ���Ľ������
		cur_node = p->next;			// �ƶ���ǰ���
		x = p->data;				// ȡ��������������ֵ
		delete p;					// �ͷŴ�ɾ���Ľ��
	}
	num--;
	return x;
}

template <typename T>
T LinkList<T>::ModifyData(const T& t) throw(int)// �޸�(�滻)��ǰ������������ֵ
{
	if (cur_node == NULL)
		throw - 1;
	T x = cur_node->data;			// ȡ����ǰ�������������ֵ
	cur_node->data = t;				// �滻����������ֵ
	return x;
}

template <typename T>
int LinkList<T>::NumNodes() const				// ���ؽ����
{
	return num;
}

template <typename T>
int LinkList<T>::CurPos() const					// ���ص�ǰ������ţ�-1��ʾ�޵�ǰ��㣩
{
	if (cur_node == NULL)
		return -1;
	int n = 0;
	Node<T>* p;
	for (p = head; p != NULL && p != cur_node; p = p->next, n++)
		;
	if (p == NULL)									// ��ʱ��cur_nodeָ����
		return -1;
	return n;
}

template <typename T>
Node<T>* LinkList<T>::CurNode()					// ���ص�ǰ���ĵ�ַ��NULL��ʾ�޵�ǰ��㣩
{
	return cur_node;
}

template <typename T>
T& LinkList<T>::CurData() throw(int)			// ���÷��ص�ǰ����������Ա���������ñ��ʽ������ֵ
{
	if (cur_node != NULL)
		return cur_node->data;
	else
		throw - 1;
}

template <typename T>
Node<T>* LinkList<T>::GoTop()					// ��ǰ�����Զ�λ���׽�㡢��n�����(n��0��)��β���
{
	return cur_node = head;
}

template <typename T>
Node<T>* LinkList<T>::Go(int n)					// ��ǰ�����Զ�λ���׽�㡢��n�����(n��0��)��β���
{
	if (n<0 || n>num)
		return cur_node = NULL;
	int i = 0;
	cur_node = head;
	while (cur_node != NULL && i < n)
	{
		cur_node = cur_node->next;
		i++;
	}
	return cur_node;
}

template <typename T>
Node<T>* LinkList<T>::GoBottom()				// ��ǰ�����Զ�λ���׽�㡢��n�����(n��0��)��β���
{
	if (head == NULL)								// ������ʱ
		cur_node = NULL;
	for (cur_node = head; cur_node->next != NULL; cur_node = cur_node->next)	// ��ʱ����ǿգ�cur_node->next�Ϸ�
		;
	return cur_node;
}

template <typename T>
Node<T>* LinkList<T>::Skip(int n) throw(int)	// ��ǰ�����Զ�λ��n��Ϊ��������Ĭ��nΪ1��ʾ��һ�����
{
	if (cur_node == NULL)
		throw - 1;
	int m = CurPos() + n;
	return cur_node = Go(m);
}

template <typename T> template <typename TYPE>
Node<T>* LinkList<T>::Locate(const TYPE& x, bool newsearch) // ��ǰ���������������TYPE���ͣ���λ
{
	static Node<T>* p = head;
	static TYPE data = x;
	if (newsearch)
	{
		p = head;
		data = x;
	}
	for (; p != NULL && TYPE(p->data) != TYPE(data); p = p->next)	// forѭ���ı��ʽ1Ϊ�գ��������"��ǰ"������������
		;													// TYPE()Ϊ����ǿ��ת�������
	cur_node = p;
	if (p != NULL)		// ����ҵ����ڷ����ҵ��Ľ���ַ��cur_node��֮ǰ��p"����"����ǰ��һ����Ϊ������������׼��
		p = p->next;
	return cur_node;
}

template <typename T> template <typename TYPE>
void LinkList<T>::Sort(const TYPE& x, bool ascending)	// ����TYPE���������������
{
	if (head == NULL || head->next == NULL) return;
	Node<T>* p, * pGuard, * rest;
	// ���Ƚ�ԭ��������������
	rest = head->next;			// ������ԭ��һ�������
	head->next = NULL;			// ���������������ԭ�� 0 �����
	// ���δ���ֱ������Ϊ��
	while (rest != NULL)
	{
		p = rest;
		rest = rest->next;		// ж�¾������ס����
		if ((ascending && ((TYPE)p->data < (TYPE)head->data)) || (!ascending && TYPE(p->data) > TYPE(head->data)))
		{
			p->next = head;
			head = p;
			continue;
		}
		pGuard = head;
		while (pGuard->next != NULL &&
			((ascending && TYPE(pGuard->next->data) <= TYPE(p->data)) ||
				(!ascending && TYPE(pGuard->next->data) >= TYPE(p->data))))
			pGuard = pGuard->next;
		p->next = pGuard->next;
		pGuard->next = p;
	}
}

template <typename T>
void LinkList<T>::Reverse()						// �����㵹��
{
	if (head == NULL || head->next == NULL)			// ����������������������
		return;
	// ���Ƚ�ԭ��������������
	Node<T>* p, * rest = head->next;				// ��ԭ����ĵڶ����������β��㣬��Ϊ��ʣ������rest
	head->next = NULL;							// ��ԭ������׽ڵ���Ϊһ��������Ŀǰ����һ����㣩
	while (rest != NULL)							// ����ʣ�����������꼴����ѭ��
	{
		p = rest;
		rest = rest->next;						// ����ʣ���������׽ڵ�ж�£�����ɾ��������p��ס
		p->next = head;
		head = p;								// ��ж�µĽ�������������ײ�
	}											// ע�⣺����ֻ�޸��˸�����next��ֵ��cur_node����
}
#endif
