#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "huffmantree.h"
int compress(HuffNode huf_tree[], int n, long flength, char *ifname, char *ofname)
{
	FILE * inFile = fopen(ifname, "rb");//��Ҫѹ���ļ�
	FILE * outFile = fopen(ofname, "wb");//��ѹ�����ļ�

	unsigned char temp = '\0';            //8bit��ʱ�ı���

	char buffer[256] = "\0";           //������

	char tou[20];                     //�ļ���׺���ַ�����
	int z = 0;
	int strLen = strlen(ifname);//�ļ���׺������
	for (int g = strLen - 1; g>0; g--)//��ȡ�ļ���׺�����Ӻ����ȡ��
	{
		if (ifname[g] == '.')//��ȡ�ļ���׺�����һ����.��
		{
			for (int k = g; k< strLen; k++)
			{
				z++;
				tou[z] = ifname[k];

			}
		}
	}

	tou[0] = z + '0';//��ȡ�ļ���׺������(ת���ַ�)
	fwrite((char *)&tou, sizeof(char), z + 1, outFile);//���ļ�ͷ��
	fwrite(&flength, sizeof(long), 1, outFile);//���ܳ���
	fwrite(&n, sizeof(int), 1, outFile);//���ַ�������

	for (int i = 0; i < n; i++) {//��ÿ����Ŷ�Ӧ���ַ�,Ȩ��
		fwrite(&huf_tree[i].ch, sizeof(unsigned char), 1, outFile);
		fwrite(&huf_tree[i].weight, sizeof(long), 1, outFile);
		/*for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)
		{
		fwrite(&huf_tree[i].bits[f], sizeof(char), 1, outFile);
		}*/
	}


	while (fread(&temp, sizeof(unsigned char), 1, inFile))//�ļ���Ϊ��
	{
		for (int i = 0; i <n; i++)//�Ҷ�Ӧ�ַ�
		{
			if (temp == huf_tree[i].ch)
			{
				for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)//���˵���0��1�ı��루��������ı׶ˣ�
				{
					strncat(buffer, &huf_tree[i].bits[f], 1);//����������ֵ
				}
			}

		}
		while (strlen(buffer) >= 8)//���������ڵ���8��bits����ѭ�� 
		{
			temp = 0;
			for (int i = 0; i < 8; i++)//ÿ8��bitsѭ��һ��
			{
				temp = temp << 1;//����1
				if (buffer[i] == '1')//�����Ϊ1���Ͱ�λΪ1
				{
					temp = temp | 0x01;//�ڲ�Ӱ������λ������£����λ��1
				}
			}
			fwrite(&temp, sizeof(unsigned char), 1, outFile);//д���ļ�
			strcpy(buffer, buffer + 8);//��д���ļ���bitsɾ��
		}
	}
	int m = strlen(buffer);//��ʣ�಻��Ϊ8��bits�ĸ�����l
	if (m) {
		temp = 0;
		for (int i = 0; i < m; i++)
		{
			temp = temp << 1;//�ƶ�1
			if (buffer[i] == '1')//�����Ϊ1���Ͱ�λΪ1
			{
				temp = temp | 0x01;
			}

		}
		temp <<= 8 - m;// // �������ֶδ�β���Ƶ��ֽڵĸ�λ
		fwrite(&temp, sizeof(unsigned char), 1, outFile);//д�����һ��
	}

	fclose(inFile);
	fclose(outFile);
	return 1;
}//compress
int extract(HuffNode huf_tree[],  char *ifname, char *ofname)
{
	int i;
	char huozui;                          //�ļ���׺����
	char tou[20];                         //�ļ���׺�ַ�
	long flength;                         //�ļ��ܳ���
	int n;                               //�ַ�����
	int node_num;                        //�������
	unsigned long writen_len = 0;		// �����ļ�д�볤��
	FILE *infile, *outfile;
	unsigned char code_temp;		// �ݴ�8bits����
	unsigned int root;		// ������ڵ���������ƥ�����ʹ��

	infile = fopen(ifname, "rb");		// �Զ����Ʒ�ʽ��ѹ���ļ�
	// �ж������ļ��Ƿ����
	if (infile == NULL)
		return -1;

	//��ȡ�ļ���׺������
	fread(&huozui, sizeof(char),1,infile);
	//�ַ�ת����
	int huozui_du = huozui - '0';
	//��ȡ�ļ���׺�ַ�
	fread(&tou, sizeof(char), huozui_du, infile); //��ȡ�ļ���׺�ַ�
	fread(&flength, sizeof(long), 1, infile);    //��ȡ�ļ��ܳ���
	fread(&n, sizeof(int), 1, infile);          //��ȡ�ַ�����

	node_num = 2 * n - 1;		// �����ַ������������㽨������������������ 
		
	// ��ʼ����
	for (int a = 0; a < 512; a++)    
	{
		huf_tree[a].parent = -1;
		huf_tree[a].ch = NULL;
		huf_tree[a].weight = -1;
		huf_tree[a].lchild = -1;
		huf_tree[a].rchild = -1;
	}

	// ��ȡѹ���ļ�ǰ�˵��ַ�����ӦȨ�أ������ؽ���������
	for (i = 0; i < n; i++)
	{
		fread((char *)&huf_tree[i].ch, sizeof(unsigned char), 1, infile);		// �����ַ�
		fread((char *)&huf_tree[i].weight, sizeof(long), 1, infile);	// �����ַ���ӦȨ��
	}

	CreateHuffmanTree(huf_tree, n);//��������������ָ�뺢�Ӹ��ױ�ʾ��
	HuffmanCoding(huf_tree, n);//���ɹ���������


	//printf("\n");
	//for (int d = 0; d < 2 * n - 1; d++)//��������
	//{
	//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, huf_tree[d].ch, huf_tree[d].count, huf_tree[d].parent, huf_tree[d].lch, huf_tree[d].rch);  /* ���ڲ��� */

	//	for (int f = 0; huf_tree[d].bits[f] == '0' || huf_tree[d].bits[f] == '1'; f++)
	//		printf("%c", huf_tree[d].bits[f]);
	//	printf("\n");
	//}

	strncat(ofname, tou, huozui_du);

	outfile = fopen(ofname, "wb");		// ��ѹ�������ɵ��ļ�
	root = node_num - 1;                //�������±�
	while (1)
	{
		fread(&code_temp, sizeof(unsigned char), 1, infile);		// ��ȡһ���ַ����ȵı���

		// �����ȡ��һ���ַ����ȵı��루ͨ��Ϊ8λ��
		for (i = 0; i < 8; i++)
		{
			// �ɸ�����ֱ��Ҷ�ڵ�����ƥ������Ӧ�ַ�������
			if (code_temp & 128)//128��1000 0000   ��λ����Ǳ��뻺������λ�Ƿ�Ϊ1
				root = huf_tree[root].rchild;//Ϊ1��root=������
			else
				root = huf_tree[root].lchild;//Ϊ0��root=������

			if (root < n)//0��n-1����������Ϊ-1
			{
				fwrite(&huf_tree[root].ch, sizeof(unsigned char), 1, outfile);
				writen_len++;//�ѱ����ַ���һ
				if (writen_len == flength) break;		// �����ļ����ȣ������ڲ�ѭ��
				root = node_num - 1;        // ��λΪ��������ƥ����һ���ַ�
			}
			code_temp <<= 1;		// �����뻺�����һλ�Ƶ����λ���ṩƥ��
		}
		if (writen_len == flength) break;		// �����ļ����ȣ��������ѭ��
	}

   //�ر��ļ�
	fclose(infile);
	fclose(outfile);
	return 1;
}//extract()