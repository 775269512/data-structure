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
	//变量段定义
	int n=BYTESIZE;//有效字节
	int opt, flag=1;
	HuffNode hufftree[512];//最多511个结点

	while (1)
	{
		/*菜单*/
		showmenu();
		/*变量初始化*/
		opt = flag = 0;	// 每次进入循环都要初始化flag为0
		char ifname[256];
		char ofname[256];		// 保存输入输出文件名
		for (int a = 0; a < 512; a++)
		{
			hufftree[a].parent = -1;
			hufftree[a].ch = NULL;
			hufftree[a].weight = -1;
			hufftree[a].lchild = -1;
			hufftree[a].rchild = -1;
		}
		//table逻辑
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
