#pragma once
typedef struct
{
	int weight;
	int parent, lchild, rchild;

}HTNode,*HuffmanTree;
typedef char** HuffmanCode;
void setHuffmantree(HuffmanTree &HT, int *w, int n);//������������
void select(HuffmanTree HT, int n, int &s1, int &s2);//��HT[1~I-1��ѡ��parentΪ����Ϊ��С������������ŷֱ�Ϊs1,s2
void Huffcoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
void setHuffmancode(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);