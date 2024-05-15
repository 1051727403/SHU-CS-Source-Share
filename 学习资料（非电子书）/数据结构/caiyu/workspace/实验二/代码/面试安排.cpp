#include <iostream>
#include <cstdio>
using namespace std;

bool flag;
int n,k,m;


class Node
{
	public:
		Node(int a):data(a),pre(NULL),nxt(NULL){}
		friend class Circle;
		int getdata(){return data;}
	private:
		int data;
		Node *pre,*nxt;
};

class Circle
{
	public:
		Circle(int n)
		{
			len=n;head=NULL;
			for(int i=1;i<=n;++i)
				Append(i);
		}
		void Append(int a)
		{
			if(!head)
			{
				head=new Node(a);
				head->pre=head;
				head->nxt=head;
				head->data=a;
				return;
			}
			Node *tmp=head->pre;
			Node *p=new Node(a);
			tmp->nxt=p;
			p->pre=tmp;
			head->pre=p;
			p->nxt=head;
			p->data=a;
		}
		Node* Findx(int cnt)
		{
			Node *p=x;
			for(int i=1;i<cnt;++i)
				p=p->nxt;
			x=p->nxt;
			return p;
		}
		Node* Findy(int cnt)
		{
			Node *p=y;
			for(int i=1;i<cnt;++i)
				p=p->pre;
			y=p->pre;
			return p;
		}
		void Delete(Node *p)
		{
			len--;
			if(p==x) x=x->nxt;
			if(p==y) y=y->pre;
			if(head==head->nxt)
			{
				x=y=NULL;
				head->pre=head->nxt=head=NULL;
				delete p;
				return;
			}
			p->nxt->pre=p->pre;
			p->pre->nxt=p->nxt;
			delete p;
		}
		bool IsEmpty()
		{
			return len==0;
		}
		static void Setpos(Circle c)
		{
			x=c.head;
			y=c.head->pre;
		}
	private:
		static Node *x,*y;
		int len;
		Node *head;
};
Node* Circle::x=NULL;
Node* Circle::y=NULL;

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	k++;m++; 
	Circle resume(n);
	if(!resume.IsEmpty())
	Circle::Setpos(resume);
	else {
		printf("Á´±íÎª¿Õ£¡\n");
		return 0;
	}
	while(!resume.IsEmpty())
	{
		Node *tmpx=resume.Findx(k);
		Node *tmpy=resume.Findy(m);
		if(flag) printf(";"); 
		if(tmpx==tmpy)
		{
			printf("%d",tmpx->getdata());
			resume.Delete(tmpx);
		}
		else if(tmpx!=tmpy)
		{
			printf("%d,%d",tmpx->getdata(),tmpy->getdata());
			resume.Delete(tmpx);
			resume.Delete(tmpy);
		}
		flag=true;
	}
	printf("¡£"); 
	return 0; 
}
