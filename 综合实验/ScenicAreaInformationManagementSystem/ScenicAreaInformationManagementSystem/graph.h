#pragma once
#include<string>
#include<vector>
using namespace std;
#define MAX_SPOT_NUM 20//定义景区最大个数

struct Vex //点
{
	int num; //景区编号
	string spotName;//景点名称
	string spotInfo;//景点描述
};

struct Edge   //边
{
	int vex1;//边顶点1
	int vex2;//边顶点2
	int distance;//边的长度
};

typedef struct PathNode
{
	int vexIndex[MAX_SPOT_NUM];//一条路径的下标值
	PathNode* next;
	//构造函数
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
	int adjMatric[MAX_SPOT_NUM][MAX_SPOT_NUM]; //邻接矩阵
	Vex vexs[MAX_SPOT_NUM];   //顶点信息数组
	int vexNum;//图中顶点数
	int egeNum;//图中无向边数
	void DFS(int beginVexIndex, bool visited[], int &depth, PathList &pathList);//深度优先遍历（递归实现）
	bool allVisist(bool visited[], int num);//判断前n个景点是否被访问过
public:
	Graph();												//初始化图结构
	~Graph();
	bool insertVex(Vex vex);								//将顶点保存在顶点数组中
	bool insertEdge(Edge edge);								//insert an edge in the adjMatric
	Vex getVex(int vexIndex);								//search vex acording to vexIndex(int)
	int findEdge(int vexIndex, Edge aEdge[]);				//查询与指定顶点相连的边
	int getVexNum();										//获取当前顶点个数
	int getEdgeNum();										//获取当前边条数
	void prinGraphInfo();									//输出图的信息
	void printNodeInfo();									//输出图中点的信息
	void printEdgeInfo();									//输出图中边的信息
	void printVex(Vex vex);									//输出指定点信息
	void printEdge(Edge edge);								//输出指定点信息
	void DFSTravel(int beginVexIndex, PathList &pathList);  // 深度优先遍历得到一条路径
	void findShortPath(int vexStart, int vexEnd, Edge pathEdges[]);  //找到起点到终点的最短路径
	vector<Edge>  findMinTree();										// 寻找最小生成树（prim算法实现）
};
