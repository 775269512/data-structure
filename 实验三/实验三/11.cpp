#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "GreatGraph.h"
#include "Stack.h"
#define MaxVertices 100
#define MaxStackSize 100
#define Notstudy	0
#define study		1
void Topologicalsort(ALGraph G, int numterm, int uplcredit)//教学课程每学年的编排
{
	TeaNode *p;//链表结点指针
	SeqStack s;//定义一个堆栈
	int *indegree=new int(G.vexnum + 2);//入度数组
	int i, j, k;
	int count;//课程编排数目累加器
	int sumcredit;//每个学期学分的累加器
	FindInDegree(G, indegree);//找出每个结点的入度
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
		}//将入度为0的点入栈，并改变结点的状态
		if (!StackNotEmpty(s) && (sumcredit <= uplcredit))
		{
			k = k + 1;
			printf("\n");
			printf("第%d个学期学得的课程：\n", k);
			sumcredit = 0;
			for (i = 1; i <= G.vexnum; i++)
				if ((G.vertices[i].indegree == 0) && (G.vertices[i].state = Notstudy))
					StackPush(&s, i);
			while ((!StackNotEmpty(s)) && (sumcredit <= uplcredit))
			{
				StackPop(&s, &j);
				sumcredit = sumcredit + G.vertices[j].credit;//将出栈的结点的学分加到累加器上
				if (sumcredit <= uplcredit)
				{
					printf("%s", G.vertices[j].name);
					count++;//课程累加器加1
					for (p = G.vertices[j].firstTea; p = NULL; p->next)
						G.vertices[p->adjvex].indegree--;//将邻接结点的入度减1
				}
				else
					StackPush(&s, j);//将超过学分上限的结点重新入栈
			}
		}
	}
	printf("\n");
	if (count<G.vexnum)
		printf("\n课程编排出错\n");
	else
	{
		printf("\n课程编排成功\n");
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