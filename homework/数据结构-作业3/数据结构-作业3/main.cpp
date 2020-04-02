
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include<queue>
using namespace std;

typedef struct BiTnode {
	char data;
	struct BiTnode *lchild, *rchild;
}BiTnode, *BiTree;
void CreateBiTree(BiTree &T)
{
	char zifu1, zifu2;
	cin>>zifu1;
	if (!(T = (BiTnode *)malloc(sizeof(BiTnode)))) exit(0);
	if (zifu1 == ';') {
		free(T);
		T = NULL; return;
	}
	else
	{
		T->data = zifu1;
		CreateBiTree(T->lchild);
	
		CreateBiTree(T->rchild);
	}
	return;
}
void PrintBiTree(BiTree T)
{

	if (T == NULL) return;
	else
	{
		cout << T->data;

		PrintBiTree(T->lchild);
		PrintBiTree(T->rchild);
	}
}
bool istree(BiTnode* T)
{
	bool flag = true;
	if (T == NULL) {

		return flag;
	}
	else if (T->lchild == NULL && T->rchild == NULL) {
		return flag;
	}
	queue<BiTnode*> q;
	BiTnode *p = T;
	q.push(T);
	int count = 1;

		p = q.front();
		q.pop();
		while (p != NULL)
		{
			q.push(p->lchild);
			q.push(p->rchild);
			p = q.front();
			q.pop();
		}//һֱ���������������ֱ�������սڵ�ʱֹͣ
		while (!q.empty())
		{
			p = q.front();
			q.pop();
			if (p != NULL) return false;//����������������սڵ���������ǿսڵ㣬��Ϊ��ȫ������

		}
		return true;
}

void PrintTheDate(int k, BiTree T,int &i)
{
	if (T != NULL)
	{
		i++;
		if (i == k)
		{
			cout << T->data; return;
		}
		else
		{
			
			PrintTheDate(k, T->lchild,i);
			
			PrintTheDate(k, T->rchild,i);
		}
	}
	return;
}
void outputDate(int k, BiTree T)
{
	int i = 0;
	PrintTheDate(k, T, i);
}
int main()
{
	BiTree T;
	cout << "�������������;����";
	CreateBiTree(T);
	PrintBiTree(T);
	if (istree(T))
		cout << "����ȫ������";
	else cout << "������ȫ������";
	int k = 5;
	outputDate(k,T);
	return 0;
}