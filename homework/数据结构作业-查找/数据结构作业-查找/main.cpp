#include<iostream>
#include<stdlib.h>
using namespace std;
#include"algorithm"
typedef float ElemType;
typedef struct BSTNode
{
	ElemType data;
	struct BSTNode *lchild, *rchild;
}BSTNode;
typedef struct BST
{
	BSTNode *root;
}BST;
bool InitBST(BST *b) //��ʼ��������
{
	b->root = NULL;
	return true;
}
bool InitBSTNode(BSTNode * &n) //��ʼ���ڵ�
{
	n = (BSTNode *)malloc(sizeof(BSTNode));
	n->lchild = NULL;
	n->rchild = NULL;
	return true;
}
bool clearBST(BSTNode * &n) //����BST
{
	if (n)
		return  false;
	if (n->lchild)
		clearBST(n->lchild);
	if (n->rchild)
		clearBST(n->rchild);
	free(n);
	return true;
}
bool insert(BST *b, ElemType e)//�ѽ�����BST
{
	BSTNode *n, *m;
	InitBSTNode(n);
	n->data = e;
	if (b->root == NULL)
	{
		b->root = n;
		return true;
	}
	m = b->root;
	while (1)//ѭ���Ƚ�
	{
		if (e<m->data)//С�ڸ��ڵ������������
		{
			if (m->lchild == NULL)
			{
				m->lchild = n;//�����Ӹ�ֵ
				return  true;
			}
			if (m->lchild != NULL && e>m->lchild->data)
			{
				n->lchild = m->lchild;
				m->lchild = n;
				return true;
			}
			else  m = m->lchild;
			continue;
		}
		else//���ڸ��ڵ������������
		{
			if (m->rchild == NULL)
			{
				m->rchild = n; //���Һ��Ӹ�ֵ
				return  true;
			}
			if (m->rchild != NULL && e<m->rchild->data)
			{
				n->rchild = m->rchild;
				m->rchild = n;
				return true;
			}
			else
				m = m->rchild;
			continue;
		}
	}
}
bool find(BST *b, ElemType e) //��ѯԪ��e����¼�ȽϵĴ�����ѯ�ɹ�����true�����򷵻�false
{
	int count = 0;
	BSTNode *x = b->root;
	while (1)//ѭ���Ƚ�
	{
		count++;//���ü�����
		if (e<x->data)//С�ڸ��ڵ������������в���
		{
			if (x->lchild == NULL)
			{
				cout << "����ʧ��,���Ҵ�����  " << count << endl;
				return false;//������Ϊ�������ʧ��
			}
			x = x->lchild;//���������ӵ�ֵ�Ƚ�
			continue;
		}
		if (e>x->data) //���ڸ��ڵ������������в���
		{
			if (x->rchild == NULL)
			{
				cout << "����ʧ��,���Ҵ�����  " << count << endl;
				return false;//������Ϊ�������ʧ��
			}
			x = x->rchild;//�������Һ��ӵ�ֵ�Ƚ�
			continue;
		}
		if (e == x->data)
		{
			cout << "���ҳɹ�,���Ҵ�����  " << count << endl;
			//cout << count;
			return  true;
		}

	}
}
int main()
{
	int n, m = 0, count;
	BST b;
	InitBST(&b);
	cout << "BST�ڵ���Ŀ��" << endl;
	cin >> n;
	ElemType *p = new ElemType[n];
	cout << "BST�ڵ����ݣ�" << endl;
	for (int i = 0; i<n; i++)
	{
		cin >> p[i];
		insert(&b, p[i]);

	}

	while (m != -1)
	{
		cout << "����Ҫ���ҵ����ݣ�����-1�������ң�" << endl;
		cin >> m;
		find(&b, m);
	}
	system("pause");
	return 0;
}
