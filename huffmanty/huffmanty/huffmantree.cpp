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
int CreateHuffmanTree(HuffNode *huf_tree, int n)//����huffman��
{
	int i;
	int s1, s2;
	for (i = n; i < 2 * n - 1; ++i)
	{
		select(huf_tree, i, &s1, &s2);		// ѡ����С���������
		huf_tree[s1].parent = i;            //ԭ��˫��Ϊi
		huf_tree[s2].parent = i;
		huf_tree[i].lchild = s1;               //�½������������С��s1
		huf_tree[i].rchild = s2;               //�½������������Сs2
		huf_tree[i].weight = huf_tree[s1].weight + huf_tree[s2].weight;////�½���Ȩֵ
	}
	return OK;
}

void select(HuffNode *huf_tree, int n, int *s1, int *s2)//��HT[1~I-1��ѡ��parentΪ����Ϊ��С������������ŷֱ�Ϊs1,s2
{
	// ����С���
	unsigned int i;
	unsigned long min = LONG_MAX;
	for (i = 0; i < n; i++)
		if (huf_tree[i].parent == -1 && huf_tree[i].weight < min)
		{
			min = huf_tree[i].weight;
			*s1 = i;//��¼�±�
		}
	huf_tree[*s1].parent = 1;   // ��Ǵ˽���ѱ�ѡ��

								// �Ҵ�С���
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
	char code_tmp[256];		// �ݴ���룬���256��Ҷ�ӣ����볤�Ȳ�����255
	code_tmp[255] = '\0';

	for (i = 0; i < n; ++i)
	{
		index = 256 - 1;	// ������ʱ�ռ��ʼ��

							// ��Ҷ����������
		for (cur = i, next = huf_tree[i].parent; next != -1; next = huf_tree[next].parent)
		{
			if (huf_tree[next].lchild == cur)
				code_tmp[--index] = '0';	// ��0��
			else
				code_tmp[--index] = '1';	// �ҡ�1��

			cur = next;

		}
		strcpy(huf_tree[i].bits, &code_tmp[index]);     // ���򱣴���뵽�������Ӧ�� index�ǵ�һ��
	}
	return OK;
}

//text

//�ڿ���̨���Huffman��ÿ���ڵ����Ϣ
void TestHufTree(HuffNode *huf_tree )
{
	for (int i = 0; i < 2 * BYTESIZE - 1; i++)
	{
		cout << "HuffmanTree�Ľ����ϢΪ��" << endl;
		cout << "pHT[i]  \t" << "weight\t" << "parent\t" << "lchild\t" << "rchild\t" << endl;
		cout << "pHT[" << i << "]  \t" << huf_tree[i].weight << "\t" << huf_tree[i].parent
			<< "\t" << huf_tree[i].lchild << "\t" << huf_tree[i].rchild << endl;
	}
}


//����������ɵĸ�������Huffman����
void TestHufCode(HuffmanCode pHC)
{
	cout << " *���ɵ�Huffman����Ϊ��" << endl;
	for (int i = 0; i<BYTESIZE; i++)
		cout << "pHC[" << setfill('0') << setw(2) << i << "] = " << pHC[i] << endl;
}

