#include<iostream>
#include<stdlib.h>
#include<string>
int compressfile(int *n, int *flag, char * ifname, char * ofname, HuffNode *hufftree)
{
	printf("������������ļ�����");
	fflush(stdin);		// ��ձ�׼����������ֹ����gets������ȡ�ļ���
	cin >> ifname;
	printf("���������ɵ��ļ�����");
	fflush(stdin);
	cin >> ofname;

	//���ļ����ֽڳ���
	FILE *file;
	file = fopen(ifname, "r");
	fseek(file, SEEK_SET, SEEK_END);
	long flength = ftell(file);
	fclose(file);

	*n = readFILE(hufftree, ifname);//��ȡ�ļ��������ֽ�Ƶ�����򣬷�����Ч�ֽڣ�Ƶ�ʲ�Ϊ0��
	CreateHuffmanTree(hufftree, *n);//��������������ָ�뺢�Ӹ��ױ�ʾ��
	HuffmanCoding(hufftree, *n);//���ɹ���������

								//for (int d = 0; d < 2 * n - 1; d++)//��������
								//{
								//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, hufftree[d].ch, hufftree[d].count, hufftree[d].parent, hufftree[d].lch, hufftree[d].rch);  /* ���ڲ��� */

								//	for (int f = 0; hufftree[d].bits[f] == '0' || hufftree[d].bits[f] == '1'; f++)
								//		printf("%c", hufftree[d].bits[f]);
								//	printf("\n");
								//}
	int isok = compress(hufftree, *n, flength, ifname, ofname);	// ѹ��������ֵ�����ж��Ƿ��ļ���������
	if (isok != -1)
	{
		cout << ifname << "����ѹ���С���" << endl;
		cout << ofname << "ѹ����ϡ���" << endl;
	}
	return 1;
}
int decompressfile(char * ifname, char * ofname, int *flag, HuffNode *hufftree)
{
	printf("������������ļ�����");
	fflush(stdin);		// ��ձ�׼����������ֹ����gets������ȡ�ļ���
	cin >> ifname;
	printf("���������ɵ��ļ�����");
	fflush(stdin);
	cin >> ofname;

	int isexit = extract(hufftree, ifname, ofname);		// ��ѹ������ֵ�����ж��Ƿ��ļ���������

	if (isexit != -1)
	{
		cout << ifname << "���ڽ�ѹ�С���\n";
		cout << ofname << "��ѹ��ϡ���\n";
	}
	return 1;
}
void  showmenu()
{
	printf(" =======================================\n");
	cout << "        ***Huffman�ļ�ѹ��***" << endl;
	printf(" =======================================\n");
	printf("            ��  1��ѹ��              \n");
	printf("            ��  2����ѹ              \n");
	printf("            ��  3���˳�              \n");
	printf("         �� ���������Ĳ�����         \n");
}