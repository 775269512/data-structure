#include"Tourism.h"
#include"graph.h"
#include<fstream>
#include<stack>
#include<iostream>
using namespace std;

Tourism::Tourism()
{
	mGraph = new Graph();//初始化图
}

Tourism::~Tourism()
{
	delete mGraph;
	mGraph = NULL;
}

bool Tourism::createGraph()
{
	fstream InFile;
	int vexNum = 0;
	bool insertVexReslut;
	Vex vex;
	InFile.open("vexs.txt", ios::in);
	if (!InFile.is_open())
	{
		cout << "打开文件失败" << endl;
		return false;
	}
	InFile >> vexNum;
	for (int icount = 0; icount < vexNum; icount++)
	{
		//从文件读取一个点的信息
		InFile >> vex.num >> vex.spotName >> vex.spotInfo;
		insertVexReslut = mGraph->insertVex(vex);
		if (!insertVexReslut)
			break;
	}
	InFile.close();
	if (!insertVexReslut)
	{
		cout << "插入景点失败!景点信息超限制！" << endl;
		return false;
	}
	// 从文件读取景点边的信息
	bool insertEdgeResult;
	Edge edge;
	InFile.open("edges.txt", ios::in);
	if (!InFile.is_open())
	{
		cout << "打开文件edges.txt失败！" << endl;
		return false;
	}
	while (!InFile.eof())
	{
		InFile >> edge.vex1 >> edge.vex2 >> edge.distance;
		insertEdgeResult = mGraph->insertEdge(edge);
		if (false == insertEdgeResult)
			break;
	}
	if (!insertEdgeResult)
	{
		cout << "插入景点间的边失败！" << endl;
		return false;
	}
	// 显示图的信息
	cout << "\n景点图创建成功，景点详情信息如下" << endl;
	mGraph->prinGraphInfo();
	return true;
}

void Tourism::querySpotInfo()
{
	int querynum; 
	Vex queryVex;
	Edge *qureyEdge=new Edge[MAX_SPOT_NUM];
	int Edgecount;
	cout << "请输入想要查询的景点编号：";
	cin >> querynum;
	queryVex=mGraph->getVex(querynum);
	mGraph->printVex(queryVex);
	cout << "--------周边景点----------" << endl;
	Edgecount=mGraph->findEdge(querynum,qureyEdge);
	for (int icount = 0; icount < Edgecount; icount++)
	{
		mGraph->printEdge(qureyEdge[icount]);
	}

}

void Tourism::travelPath()
{
	if (mGraph->getVexNum() == 0)
	{
		cout << "当系统中没有顶点，请检查图是否创建" << endl;
		return;
	}
	cout << "----旅游景点导航----" << endl;
	mGraph->printNodeInfo();
	int beginVexIndex = -1;
	cout << "请输入起始景区的编号:";
	cin >> beginVexIndex;
	if (beginVexIndex >= mGraph->getVexNum())
	{
		cout << "输入的景区编号有误！" << endl;
		return;
	}
	/*
	*生成遍历路线
	*/
	PathList pathlist = new PathNode;
	PathList pathlistTail = pathlist;
	mGraph->DFSTravel(beginVexIndex, pathlistTail);
	/*
	*打印路线
	*/
	cout << "导游路线为:\n";
	int  routeCountNum = 0;
	while (pathlist->next != NULL)
	{
		cout << endl << "路线" << ++routeCountNum << ":" << endl;
		for (int icount = 0; icount < mGraph->getVexNum() - 1; icount++)
		{
			cout << (mGraph->getVex(pathlist->vexIndex[icount])).spotName<< "->";
		}
		cout << mGraph->getVex(pathlist->vexIndex[mGraph->getVexNum() - 1]).spotName << endl;
		pathlist = pathlist->next;//下一条路线

	}

}

void Tourism::findShortPath()
{
	cout << endl << "-----搜索最短路径-----" << endl;
	if (mGraph->getVexNum() == 0)
	{
		cout << "当系统中没有顶点，请检查图是否创建" << endl;
		return;
	}
	//输入起止景点
	mGraph->printNodeInfo();
	int vexStart, vexEnd;
	cout << "请依次输入开始景点与终止景点的编号：";
	cin >> vexStart >> vexEnd;
	//编号异常判断
	if (vexStart >= mGraph->getVexNum() || vexEnd >= mGraph->getVexNum())
	{
		cout << "输入的景区编号有误！" << endl;
		return;
	}
	// path[i]对应着迪杰斯特拉算法过程中，第i个结点到源点最短路径中，
	// 上一个中转结点的下标（当前结点的前驱）以及到源点的最短距离
	Edge path[MAX_SPOT_NUM];
	mGraph->findShortPath(vexStart, vexEnd, path);

	// 从后往前回溯 此处设置一个栈方便输出
	stack<int> s;
	int index = vexEnd;
	while (1)
	{
		s.push(index);
		index = path[index].vex1;
		if (index == vexStart)
			break;
	}
	cout << "\n最短的游览路径如下：" << endl;
	cout << mGraph->getVex(vexStart).spotName;

	while (!s.empty())
	{
		cout << " ->" << mGraph->getVex(s.top()).spotName;
		s.pop();
	}
	cout << "    总长 " << path[vexEnd].distance << " 米" << endl << endl;
}

void Tourism::designPath()
{
	if (mGraph->getVexNum() == 0)
	{
		cout << "当前图中没有顶点，请检查是否已经创建图" << endl;
		return;
	}
	vector<Edge> edges = mGraph->findMinTree();
	int totalCost = 0;
	cout << "\n======电线铺设情况如下======\n";
	for (vector<Edge>::iterator iter = edges.begin(); iter != edges.end(); iter++)
	{
		cout << mGraph->getVex(iter->vex1).spotName << " -- " <<
			mGraph->getVex(iter->vex2).spotName << iter->distance << "米" << endl;

		totalCost += iter->distance;
	}
	cout << "铺设电线总长度为：" << totalCost << "米" << endl << endl;
}
