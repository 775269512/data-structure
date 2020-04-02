#include<iostream>
#include<stdlib.h>
#include<string>
#include"huffmantree.h"
#include"ioimg.h"
#include "FILEio.h"
#include"main.h"
using namespace std;
int main()
{
	//�����ζ���
	int n=BYTESIZE;//��Ч�ֽ�
	int opt, flag=1;
	HuffNode hufftree[512];//���511�����

	while (1)
	{
		/*�˵�*/
		showmenu();
		/*������ʼ��*/
		opt = flag = 0;	// ÿ�ν���ѭ����Ҫ��ʼ��flagΪ0
		char ifname[256];
		char ofname[256];		// ������������ļ���
		for (int a = 0; a < 512; a++)
		{
			hufftree[a].parent = -1;
			hufftree[a].ch = NULL;
			hufftree[a].weight = -1;
			hufftree[a].lchild = -1;
			hufftree[a].rchild = -1;
		}
		//table�߼�
		scanf("%d", &opt);
		switch (opt) {

		case 1:
		{

			compressfile(&n, &flag,ifname,ofname,hufftree);
			break;
		}
		case 2:
		{
			decompressfile(ifname, ofname, &flag, hufftree);
			break;
		}
		case 3:
			return 0;
		default:
			;
		}	
	}
	return 0;
}
