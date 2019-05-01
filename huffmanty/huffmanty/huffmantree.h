#ifndef HUFFMANIMAGECOMPRESSION_HUFFMANCOMPRESSION_H
#define HUFFMANIMAGECOMPRESSION_HUFFMANCOMPRESSION_H

#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define ERROR  -1
#define OK 0
#define BYTESIZE 256
#define MAXVALUE 999999
#define MaxSize 50
#define MAX 32767
using namespace std;

// Huffman���ڵ�
struct HuffNode
{
	unsigned char ch;  //�ֽڷ�
	int weight;  //�ֽڳ���Ƶ��
	int parent; //���ڵ�
	int lchild;  //����
	int rchild;  //�Һ���
	char bits[256]; // ����������
};

// Huffman��
typedef char** HuffmanCode;
int CreateHuffmanTree(HuffNode *huf_tree, int n);//����huffman��;        /* ����Huffman��;  */
void select(HuffNode *huf_tree, int n, int *s1, int *s2);    /* ������С�ʹ�С���;  */
int HuffmanCoding(HuffNode *huf_tree, int n);            /* ����Huffman����;  */


void TestHufTree(HuffNode *huf_tree );//�ڿ���̨���Huffman��ÿ���ڵ����Ϣ						 
void TestHufCode(HuffmanCode pHC);//����������ɵĸ�������Huffman����

#endif