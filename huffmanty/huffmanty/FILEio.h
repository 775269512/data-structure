#ifndef FILE_IO_DEF
#define FILE_IO_DEF
#include "huffmantree.h"
// �ļ�ͷ
struct HEAD
{
	char type[4];		// �ļ�����
	int length;		// ԭ�ļ�����
	int weight[BYTESIZE];	// Ȩֵ��ֵ
};
//�ļ��ṹ��
struct FILESTRUCT
{
	int sum;
	int fileid;
};
int readFILE(HuffNode hufftree[], string InFile);//��ȡ�ļ���Ϣ
#endif
