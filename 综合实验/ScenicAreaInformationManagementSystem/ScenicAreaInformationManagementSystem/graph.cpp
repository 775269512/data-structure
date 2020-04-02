#include"graph.h"
#include<iostream>
Graph::Graph()//��ʼ��ͼ�ṹ
{
	for (int i = 0; i < MAX_SPOT_NUM; i++)
	{
		for (int j = 0; j < MAX_SPOT_NUM; j++)
		{
			// ��ʼ���ڽӾ���Ϊ-1����ʾ���ж���֮�䲻���ڱ�
			adjMatric[i][j] = -1;
		}
	}
	// ��ʼ�������Ϊ0
	vexNum = 0;
	// ��ʼ���߸���Ϊ0
	egeNum = 0;
}

Graph::~Graph() {}
void Graph::DFS(int beginVexIndex, bool visited[], int & depth, PathList & pathList)
{
	visited[beginVexIndex] = true;
	pathList->vexIndex[depth] = beginVexIndex;		//	��ǰ����¶�Ӧ�ķ��ʽڵ�
	//������нڵ㱻���ʹ����½�һ��·�߽ڵ�
	if (allVisist(visited, vexNum) == true)
	{
		//�½�һ���ڵ�
		PathNode *newNode = new PathNode;
		newNode->next = NULL;
		// ������λ��ǰ��ֵȫ������
		for (int i = 0; i < vexNum; i++)
		{
			newNode->vexIndex[i] = pathList->vexIndex[i];
		}
		// ����ͷΪ�½�������һ��
		pathList->next = newNode;
		pathList = pathList->next;
	}
	//������нڵ�δ�߹�
	for (int icount = 0; icount < vexNum; icount++)
	{
		if (adjMatric[beginVexIndex][icount] != -1 && visited[icount] == false)
		{
			//������һ��
			depth++;
			DFS(icount, visited, depth, pathList);
			visited[icount]=false;
			depth--;//�´�ѭ����������·��
		}
	}

}

bool Graph::allVisist(bool visited[], int num)
{
	for (int icount = 0; icount < num; icount++)
	{
		//  ֻҪ��һ����û�����ʣ��ͷ���false
		if (false == visited[icount])
			return false;
	}
	return true;
}

bool Graph::insertVex(Vex vex)
{
	if (vexNum == MAX_SPOT_NUM)
		return false;
	vexs[vexNum++] = vex;
	return true;
}

bool Graph::insertEdge(Edge edge)
{
	if (edge.vex1 < 0 || edge.vex2 < 0 || edge.vex1 >= MAX_SPOT_NUM || edge.vex2 >= MAX_SPOT_NUM)
	{
		cout << "����Ϣ�±�Խ�磡" << endl;
		return false;
	}
	// �������Ϣ
	adjMatric[edge.vex1][edge.vex2] = edge.distance;
	adjMatric[edge.vex2][edge.vex1] = edge.distance;
	egeNum++;
	return true;
}

Vex Graph::getVex(int vexIndex)
{
	return vexs[vexIndex];
}

int Graph::findEdge(int vexIndex, Edge aEdge[])//Ѱ����vexTndex���ڵıߺ�
{
	int egeCount = 0;
	for (int icount = 0; icount< vexNum; icount++)
	{
		//���ڽӾ��������ҵ���vexIndex���ڵı�
		if (adjMatric[vexIndex][icount] != -1)
		{
			aEdge[egeCount].vex1 = vexIndex;
			aEdge[egeCount].vex2 = icount;
			aEdge[egeCount].distance = adjMatric[vexIndex][icount];
			egeCount++;
		}
	}
	return egeCount;
}

int Graph::getVexNum()
{
	return vexNum;
}

int Graph::getEdgeNum()
{
	return egeNum;
}

void Graph::prinGraphInfo()
{
	printNodeInfo();  // ��ӡ������Ϣ
	printEdgeInfo();  // ��ӡ�ߵ���Ϣ
}

void Graph::printVex(Vex vex)
{
	cout << vex.num << "--" << vex.spotName << endl<< vex.spotInfo << endl;
}

void Graph::printEdge(Edge edge)
{
	cout << getVex(edge.vex1).spotName << "->" << getVex(edge.vex2).spotName << " " << edge.distance << "m" << endl;
}

void Graph::DFSTravel(int beginVexIndex, PathList & pathList)
{
	int depth = 0;
	bool visited[MAX_SPOT_NUM] = { false };
	/*
	bool *visited = new bool[getVexNum()];
	for (int icount = 0; icount < getVexNum(); icount++)
	{
		visited[icount] = false;
	}
	*/
	DFS(beginVexIndex, visited, depth, pathList);
	
}

void Graph::findShortPath(int vexStart, int vexEnd, Edge pathEdges[])
{
	bool visited[MAX_SPOT_NUM] = { false };
	int weight[MAX_SPOT_NUM];
	// ��ʼ����������Ϊ����
	for (int i = 0; i < vexNum; i++)
	{
		weight[i] = INT_MAX;
	}
	// ��㵽����·��Ϊ0
	weight[vexStart] = 0;
	visited[vexStart] = true;
	pathEdges[vexStart].vex1 = vexStart;
	pathEdges[vexStart].vex2 = vexStart;
	pathEdges[vexStart].distance = 0;

	// ��ʼ���ڵ㣬��֪·����Ϊ��ʼ·��
	for (int i = 0; i < vexNum; i++)
	{
		if (adjMatric[vexStart][i] != -1)
		{
			weight[i] = adjMatric[vexStart][i];
			// ���i��ǰ��ΪԴ��
			pathEdges[i].vex1 = vexStart;
			pathEdges[i].vex2 = i;
			pathEdges[i].distance = adjMatric[vexStart][i];
		}
	}
	// ���·����Ӧ�ĵ��±�
	int minIndex = -1;
	// �Ѿ��߹��ĵ���
	int vexVisitedNum = 1;
	//����O(n^2)
	while (vexVisitedNum != vexNum)
	{
		int min = INT_MAX;
		int ninIndex = -1;
		for (int icount = 0; icount < vexNum; icount++)
		{
			//�ҳ�δ���ʹ��Ľڵ����ҳ���С�Ľڵ�
			if (visited[icount] == false && weight[icount] < min)
			{
				min = weight[icount];
				minIndex = icount;
			}
		}
		//�����뵱ǰ������С�ĵ�
		visited[minIndex] = true;
		vexVisitedNum++;
		//������С����ת�㣬�޸ĳ�������
		for (int jcount = 0; jcount < vexNum; jcount++)
		{
			// �����һ����û���������뵱ǰ��ת���бߣ����Ҿ�����ת��ĳ��Ⱥͱ�ԭ����С
			if ((adjMatric[minIndex][jcount] + weight[minIndex] < weight[jcount]) && (visited[jcount] == false) && (adjMatric[minIndex][jcount] != -1))
			{
				weight[jcount] = adjMatric[minIndex][jcount] + weight[minIndex];
				// ���½���ǰ��
				pathEdges[jcount].vex1 = minIndex;
				pathEdges[jcount].vex2 = jcount;
				pathEdges[jcount].distance = weight[jcount];
			}
		}
	}
}

vector<Edge> Graph::findMinTree()//(int index)
{
	vector<Edge> edgesVec;
	Edge newEdge;
	int adjvex[MAX_SPOT_NUM];	// ��ض����±�
	int lowcost[MAX_SPOT_NUM];  // ��̬������̱�����
								// ��������v0��㿪ʼ��
	lowcost[0] = 0;			// lowcost=0��ʾ�Ѿ�����������
	adjvex[0] = 0;
	for (int i = 1; i < vexNum; i++)
	{
		// ������������еĵ��б�
		if (adjMatric[0][i] != -1)
		{
			lowcost[i] = adjMatric[0][i];
			adjvex[i] = 0;
		}
		else
		{
			lowcost[i] = INT_MAX;
			adjvex[i] = 0;
		}

	}
	// ѭ�����е�
	for (int i = 1; i < vexNum; i++)
	{

		int min = INT_MAX;
		int minIndex = -1;
		// ����С��
		for (int j = 1; j < vexNum; j++)
		{
			// ������û�����������ұ���С·������
			if ((lowcost[j] != 0) && lowcost[j] < min)
			{
				min = lowcost[j];
				minIndex = j;
			}
		}
		// ��С�߶�Ӧ�ĵ����������
		lowcost[minIndex] = 0;
		// ����µıߵ��߼�������
		newEdge.vex1 = adjvex[minIndex];
		newEdge.vex2 = minIndex;
		newEdge.distance = min;
		edgesVec.push_back(newEdge);
		// ������С��
		for (int i = 1; i < vexNum; i++)
		{
			// ��û���ʹ����ұ߳��ȵ�ǰֵ��С
			if (lowcost[i] != 0 && (adjMatric[minIndex][i] != -1) && adjMatric[minIndex][i] < lowcost[i])
			{
				lowcost[i] = adjMatric[minIndex][i];
				adjvex[i] = minIndex;
			}
		}

	}
	return edgesVec;
}

void Graph::printNodeInfo()
{
	cout << "\n========����========" << endl;
	cout << "������Ŀ��" << vexNum << endl;
	for (int icount = 0; icount < vexNum; icount++)
	{
		printVex(getVex(icount));
	}
	cout << endl;
}

void Graph::printEdgeInfo()
{
	cout << "========��=========" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		for (int j = i; j < vexNum; j++)
		{
			if (adjMatric[i][j] != -1)
			{
				cout << "<V" << i << ",V" << j << "> -->" << adjMatric[i][j] << "��" << endl;
			}
		}
	}
	cout << endl;
}
