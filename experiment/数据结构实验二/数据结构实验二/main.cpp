#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"model.h"
#include<string.h>
int main()
{
	int n; char *N; int *w; char c_tmp;
	HuffmanCode HC; HuffmanTree HT;
	printf("输入字符个数");
	scanf_s("%d", &n);
	while ((c_tmp = getchar() != '\n') && c_tmp != EOF);
	N = (char *)malloc(n * sizeof(char));
	printf("输入%d个字符", n);
	for (int i = 0; i < n; i++)
	{
		scanf_s("%c", N + i);
	}
	do { c_tmp = getchar(); } while (c_tmp != '\n'&&c_tmp != EOF);
	w = (int *)malloc(n * sizeof(int));
	printf("\n输入%d个权重", n);
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", w + i);
	}
	do { c_tmp = getchar(); } while (c_tmp != '\n'&&c_tmp != EOF);
	
	Huffcoding(HT,HC,w,n);
	printf("赫夫曼树编码如下:\n\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d :%s\n", HT[i].weight, HC[i]);
	}
	return 0;
}
void Huffcoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)//构建哈夫曼编码
{
	setHuffmantree(HT, w, n);
	setHuffmancode(HT, HC, w, n);
}
void setHuffmantree(HuffmanTree &HT, int *w, int n)//构建哈弗曼树
{
	if (n <= 1) return;
	int m = 2 * n - 1; int s1 = 0, s2 = 0;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//不用零号单元
	HuffmanTree p; int i ;
	HT->lchild = HT->parent = HT->rchild = HT->weight = 0;
	for (p = HT+1, i = 1; i <= n; i++, p++, w++)
	{
		p->weight = *w;
		p->lchild = 0; p->parent = 0; p->rchild = 0;
	}
	for (1; i <= m; i++,p++)
	{
		p->weight =0;
		p->lchild = 0; p->parent = 0;  p->rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{
		select(HT, (i - 1), s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight= HT[s1].weight + HT[s2].weight;
	}
	/*
	for (i = 1; i <= m; i++)
	{
		printf(" %d %d %d %d ", HT[i].weight, HT[i].lchild, HT[i].rchild, HT[i].parent);
		printf("\n");
	}*/
}
void select(HuffmanTree HT,int nn,int &s1,int &s2)//在HT[1~I-1】选择parent为零且为最小的两个数，序号分别为s1,s2
{
	int i=1, v1, v2;
	v2 = 32767;
	v1 = 32767;
	s2 = 0;
	s1 = 0;
	for (i = 1; i <= nn; i++)
	{
		if (HT[i].parent == 0)
		{
			if (HT[i].weight < v1)
			{
				s2 = s1; v2 = v1;
				v1 = HT[i].weight;
				s1 = i;
		    }
			else if (HT[i].weight < v2)
			{
				v2 = HT[i].weight;
				s2 = i;
			}
		}
	}
	/*
	for (i = 1; i <= n; i++)
	printf(" %d ", HT[i].weight);
	printf("\n");
	*/
}
void setHuffmancode(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int f, c, i;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));	//分配n个字符编码的头指针向量
	char * cd = (char *)malloc(n * sizeof(char));			//分配求编码的工作空间
	cd[n - 1] = '\0';									//编码结束符
	for ( i = 1; i <= n; ++i) {
		int start = n - 1;
		for ( c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)		//从叶子到根逆向求编码
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);		//
	}
	free(cd);
}
void HuffmanTranslateCoding(HuffmanTree HT, int n, char* ch,char *N)
{//译码过程
	int m = 2 * n - 1;
	int i, j = 0;

	printf("After Translation:");
	while (ch[j] != '\0')//ch[]:你输入的要译码的0101010串
	{
		i = m;
		while (0 != HT[i].lchild && 0 != HT[i].rchild)//从顶部找到最下面
		{
			if ('0' == ch[j])//0 往左子树走
			{
				i = HT[i].lchild;
			}
			else//1 往右子树走
			{
				i = HT[i].rchild;
			}
			++j;//下一个路径
		}
		printf("%c", N[i - 1]);//打印出来
	}
	printf("\n");
}