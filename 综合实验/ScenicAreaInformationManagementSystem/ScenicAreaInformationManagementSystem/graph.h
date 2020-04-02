#pragma once
#include<string>
#include<vector>
using namespace std;
#define MAX_SPOT_NUM 20//���徰��������

struct Vex //��
{
	int num; //�������
	string spotName;//��������
	string spotInfo;//��������
};

struct Edge   //��
{
	int vex1;//�߶���1
	int vex2;//�߶���2
	int distance;//�ߵĳ���
};

typedef struct PathNode
{
	int vexIndex[MAX_SPOT_NUM];//һ��·�����±�ֵ
	PathNode* next;
	//���캯��
	PathNode()
	{
		for (int i = 0; i < MAX_SPOT_NUM; i++)
		{
			vexIndex[i] = -1;
		}
		next = NULL;
	}

}*PathList;
class Graph
{
private:
	int adjMatric[MAX_SPOT_NUM][MAX_SPOT_NUM]; //�ڽӾ���
	Vex vexs[MAX_SPOT_NUM];   //������Ϣ����
	int vexNum;//ͼ�ж�����
	int egeNum;//ͼ���������
	void DFS(int beginVexIndex, bool visited[], int &depth, PathList &pathList);//������ȱ������ݹ�ʵ�֣�
	bool allVisist(bool visited[], int num);//�ж�ǰn�������Ƿ񱻷��ʹ�
public:
	Graph();												//��ʼ��ͼ�ṹ
	~Graph();
	bool insertVex(Vex vex);								//�����㱣���ڶ���������
	bool insertEdge(Edge edge);								//insert an edge in the adjMatric
	Vex getVex(int vexIndex);								//search vex acording to vexIndex(int)
	int findEdge(int vexIndex, Edge aEdge[]);				//��ѯ��ָ�����������ı�
	int getVexNum();										//��ȡ��ǰ�������
	int getEdgeNum();										//��ȡ��ǰ������
	void prinGraphInfo();									//���ͼ����Ϣ
	void printNodeInfo();									//���ͼ�е����Ϣ
	void printEdgeInfo();									//���ͼ�бߵ���Ϣ
	void printVex(Vex vex);									//���ָ������Ϣ
	void printEdge(Edge edge);								//���ָ������Ϣ
	void DFSTravel(int beginVexIndex, PathList &pathList);  // ������ȱ����õ�һ��·��
	void findShortPath(int vexStart, int vexEnd, Edge pathEdges[]);  //�ҵ���㵽�յ�����·��
	vector<Edge>  findMinTree();										// Ѱ����С��������prim�㷨ʵ�֣�
};
