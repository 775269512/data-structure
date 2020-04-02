#include"graph.h"
#include<iostream>
Graph::Graph()//初始化图结构
{
	for (int i = 0; i < MAX_SPOT_NUM; i++)
	{
		for (int j = 0; j < MAX_SPOT_NUM; j++)
		{
			// 初始化邻接矩阵为-1，表示所有顶点之间不存在边
			adjMatric[i][j] = -1;
		}
	}
	// 初始化点个数为0
	vexNum = 0;
	// 初始化边个数为0
	egeNum = 0;
}

Graph::~Graph() {}
void Graph::DFS(int beginVexIndex, bool visited[], int & depth, PathList & pathList)
{
	visited[beginVexIndex] = true;
	pathList->vexIndex[depth] = beginVexIndex;		//	当前深度下对应的访问节点
	//如果所有节点被访问过，新建一个路线节点
	if (allVisist(visited, vexNum) == true)
	{
		//新建一个节点
		PathNode *newNode = new PathNode;
		newNode->next = NULL;
		// 将回溯位置前的值全部记下
		for (int i = 0; i < vexNum; i++)
		{
			newNode->vexIndex[i] = pathList->vexIndex[i];
		}
		// 链表头为新建结点的下一个
		pathList->next = newNode;
		pathList = pathList->next;
	}
	//如果还有节点未走过
	for (int icount = 0; icount < vexNum; icount++)
	{
		if (adjMatric[beginVexIndex][icount] != -1 && visited[icount] == false)
		{
			//进入下一层
			depth++;
			DFS(icount, visited, depth, pathList);
			visited[icount]=false;
			depth--;//下次循环生成其他路线
		}
	}

}

bool Graph::allVisist(bool visited[], int num)
{
	for (int icount = 0; icount < num; icount++)
	{
		//  只要有一个还没被访问，就返回false
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
		cout << "边信息下边越界！" << endl;
		return false;
	}
	// 插入边信息
	adjMatric[edge.vex1][edge.vex2] = edge.distance;
	adjMatric[edge.vex2][edge.vex1] = edge.distance;
	egeNum++;
	return true;
}

Vex Graph::getVex(int vexIndex)
{
	return vexs[vexIndex];
}

int Graph::findEdge(int vexIndex, Edge aEdge[])//寻找与vexTndex相邻的边和
{
	int egeCount = 0;
	for (int icount = 0; icount< vexNum; icount++)
	{
		//在邻接矩阵里面找到与vexIndex相邻的边
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
	printNodeInfo();  // 打印景点信息
	printEdgeInfo();  // 打印边的信息
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
	// 初始化长度数组为无穷
	for (int i = 0; i < vexNum; i++)
	{
		weight[i] = INT_MAX;
	}
	// 起点到起点的路径为0
	weight[vexStart] = 0;
	visited[vexStart] = true;
	pathEdges[vexStart].vex1 = vexStart;
	pathEdges[vexStart].vex2 = vexStart;
	pathEdges[vexStart].distance = 0;

	// 初始化节点，已知路径设为初始路径
	for (int i = 0; i < vexNum; i++)
	{
		if (adjMatric[vexStart][i] != -1)
		{
			weight[i] = adjMatric[vexStart][i];
			// 结点i的前驱为源点
			pathEdges[i].vex1 = vexStart;
			pathEdges[i].vex2 = i;
			pathEdges[i].distance = adjMatric[vexStart][i];
		}
	}
	// 最短路径对应的点下标
	int minIndex = -1;
	// 已经走过的点数
	int vexVisitedNum = 1;
	//遍历O(n^2)
	while (vexVisitedNum != vexNum)
	{
		int min = INT_MAX;
		int ninIndex = -1;
		for (int icount = 0; icount < vexNum; icount++)
		{
			//找出未访问过的节点中找出最小的节点
			if (visited[icount] == false && weight[icount] < min)
			{
				min = weight[icount];
				minIndex = icount;
			}
		}
		//访问与当前长度最小的点
		visited[minIndex] = true;
		vexVisitedNum++;
		//根据最小的中转点，修改长度数组
		for (int jcount = 0; jcount < vexNum; jcount++)
		{
			// 如果另一个点没被访问且与当前中转点有边，并且经过中转后的长度和比原来更小
			if ((adjMatric[minIndex][jcount] + weight[minIndex] < weight[jcount]) && (visited[jcount] == false) && (adjMatric[minIndex][jcount] != -1))
			{
				weight[jcount] = adjMatric[minIndex][jcount] + weight[minIndex];
				// 更新结点的前驱
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
	int adjvex[MAX_SPOT_NUM];	// 相关顶点下标
	int lowcost[MAX_SPOT_NUM];  // 动态保存最短边数组
								// 这里假设从v0结点开始找
	lowcost[0] = 0;			// lowcost=0表示已经加入生成树
	adjvex[0] = 0;
	for (int i = 1; i < vexNum; i++)
	{
		// 如果与生成树中的点有边
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
	// 循环所有点
	for (int i = 1; i < vexNum; i++)
	{

		int min = INT_MAX;
		int minIndex = -1;
		// 找最小边
		for (int j = 1; j < vexNum; j++)
		{
			// 如果结点没加入生成树且比最小路径还短
			if ((lowcost[j] != 0) && lowcost[j] < min)
			{
				min = lowcost[j];
				minIndex = j;
			}
		}
		// 最小边对应的点加入生成树
		lowcost[minIndex] = 0;
		// 添加新的边到边集向量中
		newEdge.vex1 = adjvex[minIndex];
		newEdge.vex2 = minIndex;
		newEdge.distance = min;
		edgesVec.push_back(newEdge);
		// 更新最小边
		for (int i = 1; i < vexNum; i++)
		{
			// 点没访问过，且边长比当前值还小
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
	cout << "\n========顶点========" << endl;
	cout << "顶点数目：" << vexNum << endl;
	for (int icount = 0; icount < vexNum; icount++)
	{
		printVex(getVex(icount));
	}
	cout << endl;
}

void Graph::printEdgeInfo()
{
	cout << "========边=========" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		for (int j = i; j < vexNum; j++)
		{
			if (adjMatric[i][j] != -1)
			{
				cout << "<V" << i << ",V" << j << "> -->" << adjMatric[i][j] << "米" << endl;
			}
		}
	}
	cout << endl;
}
