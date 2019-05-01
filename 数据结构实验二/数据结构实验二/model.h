#pragma once
typedef struct
{
	int weight;
	int parent, lchild, rchild;

}HTNode,*HuffmanTree;
typedef char** HuffmanCode;
void setHuffmantree(HuffmanTree &HT, int *w, int n);//构建哈弗曼树
void select(HuffmanTree HT, int n, int &s1, int &s2);//在HT[1~I-1】选择parent为零且为最小的两个数，序号分别为s1,s2
void Huffcoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
void setHuffmancode(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);