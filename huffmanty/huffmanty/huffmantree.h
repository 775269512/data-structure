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

// Huffman树节点
struct HuffNode
{
	unsigned char ch;  //字节符
	int weight;  //字节出现频度
	int parent; //父节点
	int lchild;  //左孩子
	int rchild;  //右孩子
	char bits[256]; // 哈夫曼编码
};

// Huffman树
typedef char** HuffmanCode;
int CreateHuffmanTree(HuffNode *huf_tree, int n);//构造huffman树;        /* 生成Huffman树;  */
void select(HuffNode *huf_tree, int n, int *s1, int *s2);    /* 查找最小和次小序号;  */
int HuffmanCoding(HuffNode *huf_tree, int n);            /* 生成Huffman编码;  */


void TestHufTree(HuffNode *huf_tree );//在控制台输出Huffman树每个节点的信息						 
void TestHufCode(HuffmanCode pHC);//测试输出生成的各个结点的Huffman编码

#endif