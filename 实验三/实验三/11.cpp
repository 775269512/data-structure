#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "GreatGraph.h"
#include "Stack.h"
#define MaxVertices 100
#define MaxStackSize 100
#define Notstudy	0
#define study		1
void Topologicalsort(ALGraph G, int numterm, int uplcredit)//��ѧ�γ�ÿѧ��ı���
{
	TeaNode *p;//������ָ��
	SeqStack s;//����һ����ջ
	int *indegree=new int(G.vexnum + 2);//�������
	int i, j, k;
	int count;//�γ̱�����Ŀ�ۼ���
	int sumcredit;//ÿ��ѧ��ѧ�ֵ��ۼ���
	FindInDegree(G, indegree);//�ҳ�ÿ���������
	for (i = 1;i <= G.vexnum; i++)
		G.vertices[i].indegree = indegree[i];
	    StackInitiate(&s);
	count = 0;
	k = 0;
	while (count != G.vexnum&&k <= numterm)
	{
		sumcredit = 0;
		for (i = 1; i <= G.vexnum; i++)
			if ((G.vertices[i].indegree == 0) && (G.vertices[i].state == Notstudy))
		{
			StackPush(&s, i);
			G.vertices[i].state = study;
		}//�����Ϊ0�ĵ���ջ�����ı����״̬
		if (!StackNotEmpty(s) && (sumcredit <= uplcredit))
		{
			k = k + 1;
			printf("\n");
			printf("��%d��ѧ��ѧ�õĿγ̣�\n", k);
			sumcredit = 0;
			for (i = 1; i <= G.vexnum; i++)
				if ((G.vertices[i].indegree == 0) && (G.vertices[i].state = Notstudy))
					StackPush(&s, i);
			while ((!StackNotEmpty(s)) && (sumcredit <= uplcredit))
			{
				StackPop(&s, &j);
				sumcredit = sumcredit + G.vertices[j].credit;//����ջ�Ľ���ѧ�ּӵ��ۼ�����
				if (sumcredit <= uplcredit)
				{
					printf("%s", G.vertices[j].name);
					count++;//�γ��ۼ�����1
					for (p = G.vertices[j].firstTea; p = NULL; p->next)
						G.vertices[p->adjvex].indegree--;//���ڽӽ�����ȼ�1
				}
				else
					StackPush(&s, j);//������ѧ�����޵Ľ��������ջ
			}
		}
	}
	printf("\n");
	if (count<G.vexnum)
		printf("\n�γ̱��ų���\n");
	else
	{
		printf("\n�γ̱��ųɹ�\n");
	}
}
void FindInDegree(ALGraph G, int indegree[])
{	int i;
for (i = 1; i <= G.vexnum; i++)
indegree[i] = 0;
for (i = 1; i <= G.vexnum; i++)
{
	while (G.vertices[i].firstTea)
	{
		indegree[G.vertices[i].firstTea->adjvex]++;
		G.vertices[i].firstTea = G.vertices[i].firstTea->next;
	}
}
}