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
	for (int k = 0; k < 256; k++)//初始化
		z[k].fileid = k;
    char filename[50];
	strcpy(filename, InFile.c_str());
	infile.open(filename); //打开文件
	if (!infile)
	{
		std::cout << " 打开文件失败 " << std::endl;
	}
	while (infile.get((char&)ch))//获取文件信息
	{
		for (int g = 0; g < 256; g++)
		{
			if (ch == g) //统计字符频度
				z[g].sum++;
		}
	}
	for (int m = 0; m<256; m++)//冒泡排序
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//频度从小到大排序
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
	for (int m = 0; m<256; m++)//冒泡排序
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//序号排序
			{
				int temp2 = z[n].fileid;
				z[n].fileid = z[m].fileid;
				z[m].fileid = temp2;
			}
		}
	}
	int d = 0;//有效字节
	for (int j = 0; j < 256; j++)//去掉频度为0的字符
	{
		if (z[j].sum != 0)
		{
			hufftree[d].ch = z[j].fileid;
			hufftree[d].weight = z[j].sum;
			d++;
		}
	}
	infile.close();//关闭文件
	return d;//返回字符个数
}

int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nbuf)
{
	// 生成文件名
	char filename[BYTESIZE + 5] = { '\0' };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	
	ofstream fout(filename,ios::binary);
	fout.write((char*)&sHead, sizeof(HEAD));
	fout.write(pBuffer,sizeof(char) * nbuf);
	fout.close();

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nbuf;
	cout << "压缩文件大小为：" << len << "B" << endl;
	double rate = len * 1.0 / sHead.length;
	cout.setf(ios::fixed);
	cout << "压缩率为：" << setprecision(4) << rate << "%" << endl;

	return len;
}
char Str2Byte(const char * pBinStr)//将字符串转化为字节
{
	
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;// 左移1位
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}
int Encode(const char * FileAdr, const HuffmanCode HC, char *pBuffer, const int nbuf)
{
	char cd[BYTESIZE] = { '\0' }; char d0[BYTESIZE] = { '\0' };
	// 开辟缓冲区
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	FILE *fin = fopen(FileAdr, "rb");
	if (!pBuffer)
	{
		
		cerr << "开辟缓冲区失败!" << endl;
		return ERROR;
	}
	char *pfag;
	int pos = 0;		// 缓冲区指针
	int ch;
	// 扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中。
	while ((ch = fgetc(fin)) != EOF)
	{
		strcat(cd, HC[ch]);	// 从pHC复制编码串到cd
								// 压缩编码
		while (strlen(cd) >= 8)
		{
			// 截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2Byte(cd);
			// 字符串整体左移8字节
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
	//计算缓冲区的大小  
	int nbuf = 0;
	for (int i = 0; i<BYTESIZE; i++)
	{
		nbuf += sHead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	//cout<<"nbuf = "<<nbuf<<endl; 
	char *pBuffer = NULL;
	// 开辟缓冲区
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败!" << endl;
		return ERROR;
	}

	Encode(pFilename, pHC, pBuffer, nbuf);
	if (!pBuffer)
		return ERROR;
	int result = WriteFile(pFilename, sHead, pBuffer, nbuf);
	return result;
}
