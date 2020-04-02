#include <iostream>
#include<iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "FILEio.h"
using namespace std;
int readFILE(HuffNode hufftree[], string InFile)
{
	std::fstream infile;
	unsigned char ch;
	FILESTRUCT z[256] = { 0 };
	for (int k = 0; k < 256; k++)//��ʼ��
		z[k].fileid = k;
	infile.open(InFile); //���ļ�
	if (!infile)
	{
		std::cout << " ���ļ�ʧ�� " << std::endl;
	}
	while (infile.get((char&)ch))//��ȡ�ļ���Ϣ
	{
		for (int g = 0; g < 256; g++)
		{
			if (ch == g) //ͳ���ַ�Ƶ��
				z[g].sum++;
		}
	}
	for (int m = 0; m<256; m++)//ð������
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//Ƶ�ȴ�С��������
			{
				int temp1 = z[n].sum;
				z[n].sum = z[m].sum;
				z[m].sum = temp1;

				int temp2 = z[n].fileid;
				z[n].fileid = z[m].fileid;
				z[m].fileid = temp2;
			}
		}
	}
	for (int m = 0; m<256; m++)//ð������
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//�������
			{
				int temp2 = z[n].fileid;
				z[n].fileid = z[m].fileid;
				z[m].fileid = temp2;
			}
		}
	}
	int d = 0;//��Ч�ֽ�
	for (int j = 0; j < 256; j++)//ȥ��Ƶ��Ϊ0���ַ�
	{
		if (z[j].sum != 0)
		{
			hufftree[d].ch = z[j].fileid;
			hufftree[d].weight = z[j].sum;
			d++;
		}
	}
	infile.close();//�ر��ļ�
	return d;//�����ַ�����
}

int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nbuf)
{
	// �����ļ���
	char filename[BYTESIZE + 5] = { '\0' };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	
	ofstream fout(filename,ios::binary);
	fout.write((char*)&sHead, sizeof(HEAD));
	fout.write(pBuffer,sizeof(char) * nbuf);
	fout.close();

	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nbuf;
	cout << "ѹ���ļ���СΪ��" << len << "B" << endl;
	double rate = len * 1.0 / sHead.length;
	cout.setf(ios::fixed);
	cout << "ѹ����Ϊ��" << setprecision(4) << rate << "%" << endl;

	return len;
}
char Str2Byte(const char * pBinStr)//���ַ���ת��Ϊ�ֽ�
{
	
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;// ����1λ
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}
int Encode(const char * FileAdr, const HuffmanCode HC, char *pBuffer, const int nbuf)
{
	char cd[BYTESIZE] = { '\0' }; char d0[BYTESIZE] = { '\0' };
	// ���ٻ�����
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	FILE *fin = fopen(FileAdr, "rb");
	if (!pBuffer)
	{
		
		cerr << "���ٻ�����ʧ��!" << endl;
		return ERROR;
	}
	char *pfag;
	int pos = 0;		// ������ָ��
	int ch;
	// ɨ���ļ�������Huffman�����������ѹ����ѹ������ݴ浽�������С�
	while ((ch = fgetc(fin)) != EOF)
	{
		strcat(cd, HC[ch]);	// ��pHC���Ʊ��봮��cd
								// ѹ������
		while (strlen(cd) >= 8)
		{
			// ��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2Byte(cd);
			// �ַ�����������8�ֽ�
			for (int i = 0; i < BYTESIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	fclose(fin);
	fin = NULL;
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2Byte(cd);
	}
	return OK;
}
int Compress(const char *pFilename, HuffmanCode &pHC, const HEAD sHead)
{
	//���㻺�����Ĵ�С  
	int nbuf = 0;
	for (int i = 0; i<BYTESIZE; i++)
	{
		nbuf += sHead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	//cout<<"nbuf = "<<nbuf<<endl; 
	char *pBuffer = NULL;
	// ���ٻ�����
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��!" << endl;
		return ERROR;
	}

	Encode(pFilename, pHC, pBuffer, nbuf);
	if (!pBuffer)
		return ERROR;
	int result = WriteFile(pFilename, sHead, pBuffer, nbuf);
	return result;
}