#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MaxVertices 100
#define MaxStackSize 100
#define Notstudy	0
#define study		1

typedef int DataType;

#include "Stack.h"
#include "GreatGraph.h"

int main()
{
	int numterm;          //ѧ������
	int uplcredit;        //һ��ѧ�ڵ�ѧ������
	int selectway;
	char name[12][30] = { {"�������"},{ "��ɢ��ѧ" },{ "���ݽṹ" },{"�������" },{ "���Ե���ƺͷ���" },{ "�����ԭ��" },{ "����ԭ��" },{ "����ϵͳ" },{ "�ߵ���ѧ" },{ "���Դ���" },{ "��ͨ����" },{ "��ֵ����" } };
		int number[12] = { 2,3,4,3,2,3,4,4,7,5,2,3 };
	int RC[15][2] = { { 1,2 },{ 1,4 },{ 1,12 },{ 2,3 },{ 3,5 },{ 3,7 },{ 3,8 },{ 4,5 },{ 5,7 },{ 6,8 },{ 9,10 },{ 9,11 },{ 9,12 },{ 10,12 },{ 11,6 } };
	int b = 15, a = 12;

	SeqStack s;
	ALGraph G;            //ͼG����
	printf("������ѧ��������\n");
	scanf("%d", &numterm);
	printf("������ѧ�ڵ�ѧ�����ޣ�\n");
	scanf("%d", &selectway);
	CreatGraph(&G,name, number, a, b, RC);        //����һ��ͼ
	printf("��ѡ����Ų��ԣ�1.�γ̾����ܼ��е�ǰ����ѧ�ڣ�2.�γ̾������ȷֲ�\n");
	scanf("%d", &selectway);
	Topologicalsort(G, numterm, uplcredit);//ִ�н�ѧ�γ̱���
	return 0;
}


