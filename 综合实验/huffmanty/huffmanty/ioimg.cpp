#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "huffmantree.h"
int compress(HuffNode huf_tree[], int n, long flength, char *ifname, char *ofname)
{
	FILE * inFile = fopen(ifname, "rb");//打开要压缩文件
	FILE * outFile = fopen(ofname, "wb");//打开压缩后文件

	unsigned char temp = '\0';            //8bit临时的变量

	char buffer[256] = "\0";           //缓存流

	char tou[20];                     //文件后缀名字符数组
	int z = 0;
	int strLen = strlen(ifname);//文件后缀名长度
	for (int g = strLen - 1; g>0; g--)//获取文件后缀名（从后面获取）
	{
		if (ifname[g] == '.')//获取文件后缀名最后一个“.”
		{
			for (int k = g; k< strLen; k++)
			{
				z++;
				tou[z] = ifname[k];

			}
		}
	}

	tou[0] = z + '0';//获取文件后缀名长度(转成字符)
	fwrite((char *)&tou, sizeof(char), z + 1, outFile);//存文件头部
	fwrite(&flength, sizeof(long), 1, outFile);//存总长度
	fwrite(&n, sizeof(int), 1, outFile);//存字符的种类

	for (int i = 0; i < n; i++) {//存每个编号对应的字符,权重
		fwrite(&huf_tree[i].ch, sizeof(unsigned char), 1, outFile);
		fwrite(&huf_tree[i].weight, sizeof(long), 1, outFile);
		/*for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)
		{
		fwrite(&huf_tree[i].bits[f], sizeof(char), 1, outFile);
		}*/
	}


	while (fread(&temp, sizeof(unsigned char), 1, inFile))//文件不为空
	{
		for (int i = 0; i <n; i++)//找对应字符
		{
			if (temp == huf_tree[i].ch)
			{
				for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)//过滤掉非0非1的编码（数组带来的弊端）
				{
					strncat(buffer, &huf_tree[i].bits[f], 1);//给缓存流赋值
				}
			}

		}
		while (strlen(buffer) >= 8)//缓存流大于等于8个bits进入循环 
		{
			temp = 0;
			for (int i = 0; i < 8; i++)//每8个bits循环一次
			{
				temp = temp << 1;//左移1
				if (buffer[i] == '1')//如果是为1，就按位为1
				{
					temp = temp | 0x01;//在不影响其他位的情况下，最后位置1
				}
			}
			fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入文件
			strcpy(buffer, buffer + 8);//将写入文件的bits删除
		}
	}
	int m = strlen(buffer);//将剩余不足为8的bits的个数给l
	if (m) {
		temp = 0;
		for (int i = 0; i < m; i++)
		{
			temp = temp << 1;//移动1
			if (buffer[i] == '1')//如果是为1，就按位为1
			{
				temp = temp | 0x01;
			}

		}
		temp <<= 8 - m;// // 将编码字段从尾部移到字节的高位
		fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入最后一个
	}

	fclose(inFile);
	fclose(outFile);
	return 1;
}//compress
int extract(HuffNode huf_tree[],  char *ifname, char *ofname)
{
	int i;
	char huozui;                          //文件后缀长度
	char tou[20];                         //文件后缀字符
	long flength;                         //文件总长度
	int n;                               //字符种类
	int node_num;                        //结点总数
	unsigned long writen_len = 0;		// 控制文件写入长度
	FILE *infile, *outfile;
	unsigned char code_temp;		// 暂存8bits编码
	unsigned int root;		// 保存根节点索引，供匹配编码使用

	infile = fopen(ifname, "rb");		// 以二进制方式打开压缩文件
	// 判断输入文件是否存在
	if (infile == NULL)
		return -1;

	//读取文件后缀名长度
	fread(&huozui, sizeof(char),1,infile);
	//字符转数字
	int huozui_du = huozui - '0';
	//读取文件后缀字符
	fread(&tou, sizeof(char), huozui_du, infile); //读取文件后缀字符
	fread(&flength, sizeof(long), 1, infile);    //读取文件总长度
	fread(&n, sizeof(int), 1, infile);          //读取字符种类

	node_num = 2 * n - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
		
	// 初始化后
	for (int a = 0; a < 512; a++)    
	{
		huf_tree[a].parent = -1;
		huf_tree[a].ch = NULL;
		huf_tree[a].weight = -1;
		huf_tree[a].lchild = -1;
		huf_tree[a].rchild = -1;
	}

	// 读取压缩文件前端的字符及对应权重，用于重建哈夫曼树
	for (i = 0; i < n; i++)
	{
		fread((char *)&huf_tree[i].ch, sizeof(unsigned char), 1, infile);		// 读入字符
		fread((char *)&huf_tree[i].weight, sizeof(long), 1, infile);	// 读入字符对应权重
	}

	CreateHuffmanTree(huf_tree, n);//构建哈夫曼仿真指针孩子父亲表示法
	HuffmanCoding(huf_tree, n);//生成哈夫曼编码


	//printf("\n");
	//for (int d = 0; d < 2 * n - 1; d++)//仅供测试
	//{
	//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, huf_tree[d].ch, huf_tree[d].count, huf_tree[d].parent, huf_tree[d].lch, huf_tree[d].rch);  /* 用于测试 */

	//	for (int f = 0; huf_tree[d].bits[f] == '0' || huf_tree[d].bits[f] == '1'; f++)
	//		printf("%c", huf_tree[d].bits[f]);
	//	printf("\n");
	//}

	strncat(ofname, tou, huozui_du);

	outfile = fopen(ofname, "wb");		// 打开压缩后将生成的文件
	root = node_num - 1;                //根结点的下标
	while (1)
	{
		fread(&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

		// 处理读取的一个字符长度的编码（通常为8位）
		for (i = 0; i < 8; i++)
		{
			// 由根向下直至叶节点正向匹配编码对应字符（逆向）
			if (code_temp & 128)//128是1000 0000   按位与就是编码缓存的最高位是否为1
				root = huf_tree[root].rchild;//为1，root=右子树
			else
				root = huf_tree[root].lchild;//为0，root=左子树

			if (root < n)//0到n-1的左右子树为-1
			{
				fwrite(&huf_tree[root].ch, sizeof(unsigned char), 1, outfile);
				writen_len++;//已编译字符加一
				if (writen_len == flength) break;		// 控制文件长度，跳出内层循环
				root = node_num - 1;        // 复位为根索引，匹配下一个字符
			}
			code_temp <<= 1;		// 将编码缓存的下一位移到最高位，提供匹配
		}
		if (writen_len == flength) break;		// 控制文件长度，跳出外层循环
	}

   //关闭文件
	fclose(infile);
	fclose(outfile);
	return 1;
}//extract()