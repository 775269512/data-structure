#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"huffmantree.h"
#include<string.h>
#include<iomanip>
#define OK 0
#define BYTESIZE 256
#define MAXVALUE 999999
using namespace std;
//huffmantree
int CreateHuffmanTree(HuffNode *huf_tree, int n)//构造huffman树
{
	int i;
	int s1, s2;
	for (i = n; i < 2 * n - 1; ++i)
	{
		select(huf_tree, i, &s1, &s2);		// 选择最小的两个结点
		huf_tree[s1].parent = i;            //原点双亲为i
		huf_tree[s2].parent = i;
		huf_tree[i].lchild = s1;               //新结点左子树是最小的s1
		huf_tree[i].rchild = s2;               //新结点右子树是最小s2
		huf_tree[i].weight = huf_tree[s1].weight + huf_tree[s2].weight;////新结点的权值
	}
	return OK;
}

void select(HuffNode *huf_tree, int n, int *s1, int *s2)//在HT[1~I-1】选择parent为零且为最小的两个数，序号分别为s1,s2
{
	// 找最小结点
	unsigned int i;
	unsigned long min = LONG_MAX;
	for (i = 0; i < n; i++)
		if (huf_tree[i].parent == -1 && huf_tree[i].weight < min)
		{
			min = huf_tree[i].weight;
			*s1 = i;//记录下标
		}
	huf_tree[*s1].parent = 1;   // 标记此结点已被选中

								// 找次小结点
	min = LONG_MAX;
	for (i = 0; i < n; i++)
	{
		if (huf_tree[i].parent == -1 && huf_tree[i].weight < min)
		{
			min = huf_tree[i].weight;
			*s2 = i;
		}
	}
}
int HuffmanCoding(HuffNode *huf_tree, int n)
{
	int i;
	int cur, next, index;
	char code_tmp[256];		// 暂存编码，最多256个叶子，编码长度不超多255
	code_tmp[255] = '\0';

	for (i = 0; i < n; ++i)
	{
		index = 256 - 1;	// 编码临时空间初始化

							// 从叶子向根求编码
		for (cur = i, next = huf_tree[i].parent; next != -1; next = huf_tree[next].parent)
		{
			if (huf_tree[next].lchild == cur)
				code_tmp[--index] = '0';	// 左‘0’
			else
				code_tmp[--index] = '1';	// 右‘1’

			cur = next;

		}
		strcpy(huf_tree[i].bits, &code_tmp[index]);     // 正向保存编码到树结点相应域 index是第一个
	}
	return OK;
}

//text

//在控制台输出Huffman树每个节点的信息
void TestHufTree(HuffNode *huf_tree )
{
	for (int i = 0; i < 2 * BYTESIZE - 1; i++)
	{
		cout << "HuffmanTree的结点信息为：" << endl;
		cout << "pHT[i]  \t" << "weight\t" << "parent\t" << "lchild\t" << "rchild\t" << endl;
		cout << "pHT[" << i << "]  \t" << huf_tree[i].weight << "\t" << huf_tree[i].parent
			<< "\t" << huf_tree[i].lchild << "\t" << huf_tree[i].rchild << endl;
	}
}


//测试输出生成的各个结点的Huffman编码
void TestHufCode(HuffmanCode pHC)
{
	cout << " *生成的Huffman编码为：" << endl;
	for (int i = 0; i<BYTESIZE; i++)
		cout << "pHC[" << setfill('0') << setw(2) << i << "] = " << pHC[i] << endl;
}

