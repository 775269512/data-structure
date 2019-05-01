#include<iostream>
#include<stdlib.h>
#include<string>
int compressfile(int *n, int *flag, char * ifname, char * ofname, HuffNode *hufftree)
{
	printf("请输入操作的文件名：");
	fflush(stdin);		// 清空标准输入流，防止干扰gets函数读取文件名
	cin >> ifname;
	printf("请输入生成的文件名：");
	fflush(stdin);
	cin >> ofname;

	//求文件总字节长度
	FILE *file;
	file = fopen(ifname, "r");
	fseek(file, SEEK_SET, SEEK_END);
	long flength = ftell(file);
	fclose(file);

	*n = readFILE(hufftree, ifname);//读取文件，并按字节频率排序，返回有效字节（频率不为0）
	CreateHuffmanTree(hufftree, *n);//构建哈夫曼仿真指针孩子父亲表示法
	HuffmanCoding(hufftree, *n);//生成哈夫曼编码

								//for (int d = 0; d < 2 * n - 1; d++)//仅供测试
								//{
								//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, hufftree[d].ch, hufftree[d].count, hufftree[d].parent, hufftree[d].lch, hufftree[d].rch);  /* 用于测试 */

								//	for (int f = 0; hufftree[d].bits[f] == '0' || hufftree[d].bits[f] == '1'; f++)
								//		printf("%c", hufftree[d].bits[f]);
								//	printf("\n");
								//}
	int isok = compress(hufftree, *n, flength, ifname, ofname);	// 压缩，返回值用于判断是否文件名不存在
	if (isok != -1)
	{
		cout << ifname << "正在压缩中……" << endl;
		cout << ofname << "压缩完毕……" << endl;
	}
	return 1;
}
int decompressfile(char * ifname, char * ofname, int *flag, HuffNode *hufftree)
{
	printf("请输入操作的文件名：");
	fflush(stdin);		// 清空标准输入流，防止干扰gets函数读取文件名
	cin >> ifname;
	printf("请输入生成的文件名：");
	fflush(stdin);
	cin >> ofname;

	int isexit = extract(hufftree, ifname, ofname);		// 解压，返回值用于判断是否文件名不存在

	if (isexit != -1)
	{
		cout << ifname << "正在解压中……\n";
		cout << ofname << "解压完毕……\n";
	}
	return 1;
}
void  showmenu()
{
	printf(" =======================================\n");
	cout << "        ***Huffman文件压缩***" << endl;
	printf(" =======================================\n");
	printf("            ※  1：压缩              \n");
	printf("            ※  2：解压              \n");
	printf("            ※  3：退出              \n");
	printf("         ※ 请输入您的操作：         \n");
}