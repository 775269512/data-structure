#ifndef FILE_IO_DEF
#define FILE_IO_DEF
#include "huffmantree.h"
// 文件头
struct HEAD
{
	char type[4];		// 文件类型
	int length;		// 原文件长度
	int weight[BYTESIZE];	// 权值数值
};
//文件结构体
struct FILESTRUCT
{
	int sum;
	int fileid;
};
int readFILE(HuffNode hufftree[], string InFile);//读取文件信息
#endif
