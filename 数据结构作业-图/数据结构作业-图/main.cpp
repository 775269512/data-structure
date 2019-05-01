#include<stdio.h>
#include<queue>
#include<stdlib.h>
#define MAX 100
using namespace std;
struct arcnode
{
	int vertex;//�ڽӵ�
	int nofo;//Ȩֵ
	struct arcnode *nexttarc;
};
struct node
{
	int outdegree;
	int indegree;
	char data;
	struct arcnode *firstarc;
};
struct Graph
{
	struct node adjlist[MAX];
	int n;//������
	int j;//����
};

Graph setgraph()
	{
		int  k,i,j,weight;
		Graph gra;
		struct arcnode *p;
		printf("�����붥����");
		scanf_s("%d", &gra.n);
		for (i = 0; i <= gra.n; i++)
		{
			gra.adjlist[i].indegree = 0;
			gra.adjlist[i].outdegree = 0;
			gra.adjlist[i].firstarc = NULL;
		}
		char c1, c2;
		printf("����߼���(����,�������ݣ��ڽӵ㣬�ڽӵ����ݣ�Ȩֵ)\n");
		scanf_s("%d,%c,", &k, &c1);
		scanf_s("%d,%c,%d", &j, &c2, &weight);
		while(k >= 1 && j >= 1 && k <= gra.n && j <= gra.n)
		{	
		
				gra.j++;//������һ
				gra.adjlist[k].outdegree++;//��������һ
				gra.adjlist[j].indegree++;//��ȼ�һ
				gra.adjlist[k].data = c1;
				gra.adjlist[j].data = c2;
				p = gra.adjlist[k].firstarc;
				gra.adjlist[k].firstarc = (arcnode*)malloc(sizeof(arcnode));
				gra.adjlist[k].firstarc->nofo = weight;
				gra.adjlist[k].firstarc->vertex = j;
				if (p == NULL)//��ͷ����
					gra.adjlist[k].firstarc->nexttarc = p;
				else
				{
					gra.adjlist[k].firstarc->nexttarc = p->nexttarc;
				}
				printf("����߼���(����,�������ݣ��ڽӵ㣬�ڽӵ����ݣ�Ȩֵ)\n");
				scanf_s("%d,%c,", &k, &c1);
				scanf_s("%d,%c,%d", &j, &c2, &weight);
		} 
		return gra;
}
void DFS(Graph gra, int i,bool *visit)
{
	visit[i] = true;
	printf("%c  \n", gra.adjlist[i].data);
	arcnode* p = gra.adjlist[i].firstarc;
	while (p)
	{
		if (!visit[p->vertex])
			DFS(gra, p->vertex,visit);
		p = p->nexttarc;
	}
}
void DFStraverse(Graph gra)
{
	int i;
	bool visit[MAX];
	for (i = 0; i < MAX; i++)
		visit[i] = false;
	for (i = 1; i <= gra.n; i++)
		if (!visit[i])
			DFS(gra, i, visit);

}
void BFStraverse(Graph gra)
{
	int i;
	queue<arcnode *> q2;
	bool visit[MAX];
	for (i = 0; i < MAX; i++)
		visit[i] = false;
	for (i = 1; i <= gra.n; i++)
	{
		if (!visit[i])
		{
			visit[i] = true;
			printf("%c", gra.adjlist[i].data);
			 q2.push(gra.adjlist[i].firstarc);
			while (!q2.empty())
			{
				arcnode * p = q2.front();
				q2.pop();
				while (p)
				{
					if (!visit[p->vertex])
					{
						printf("%c", gra.adjlist[p->vertex].data);
						q2.push(gra.adjlist[p->vertex].firstarc);
						visit[p->vertex] = true;
					}
					p = p->nexttarc;
				}
			}
		}

	}

}
int main()
{
    Graph G;
	G=setgraph();
	printf("������ȱ���:");
	DFStraverse(G);
	printf("\n������ȱ���:");
	BFStraverse(G);
	return 0;
}

