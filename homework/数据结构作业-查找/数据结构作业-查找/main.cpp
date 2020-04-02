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
bool InitBST(BST *b) //初始化二叉树
{
	b->root = NULL;
	return true;
}
bool InitBSTNode(BSTNode * &n) //初始化节点
{
	n = (BSTNode *)malloc(sizeof(BSTNode));
	n->lchild = NULL;
	n->rchild = NULL;
	return true;
}
bool clearBST(BSTNode * &n) //销毁BST
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
bool insert(BST *b, ElemType e)//把结点插入BST
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
	while (1)//循环比较
	{
		if (e<m->data)//小于根节点则插入左子树
		{
			if (m->lchild == NULL)
			{
				m->lchild = n;//给左孩子赋值
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
		else//大于根节点则插入右子树
		{
			if (m->rchild == NULL)
			{
				m->rchild = n; //给右孩子赋值
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
bool find(BST *b, ElemType e) //查询元素e，记录比较的次数查询成功返回true，否则返回false
{
	int count = 0;
	BSTNode *x = b->root;
	while (1)//循环比较
	{
		count++;//设置计数器
		if (e<x->data)//小于根节点则在左子树中查找
		{
			if (x->lchild == NULL)
			{
				cout << "查找失败,查找次数：  " << count << endl;
				return false;//左子树为空则查找失败
			}
			x = x->lchild;//继续与左孩子的值比较
			continue;
		}
		if (e>x->data) //大于根节点则在右子树中查找
		{
			if (x->rchild == NULL)
			{
				cout << "查找失败,查找次数：  " << count << endl;
				return false;//右子树为空则查找失败
			}
			x = x->rchild;//继续与右孩子的值比较
			continue;
		}
		if (e == x->data)
		{
			cout << "查找成功,查找次数：  " << count << endl;
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
	cout << "BST节点数目：" << endl;
	cin >> n;
	ElemType *p = new ElemType[n];
	cout << "BST节点数据：" << endl;
	for (int i = 0; i<n; i++)
	{
		cin >> p[i];
		insert(&b, p[i]);

	}

	while (m != -1)
	{
		cout << "输入要查找的数据（输入-1结束查找）" << endl;
		cin >> m;
		find(&b, m);
	}
	system("pause");
	return 0;
}
