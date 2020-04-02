#include"Tourism.h"
#include"graph.h"
#include<fstream>
#include<stack>
#include<iostream>
using namespace std;

Tourism::Tourism()
{
	mGraph = new Graph();//��ʼ��ͼ
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
		cout << "���ļ�ʧ��" << endl;
		return false;
	}
	InFile >> vexNum;
	for (int icount = 0; icount < vexNum; icount++)
	{
		//���ļ���ȡһ�������Ϣ
		InFile >> vex.num >> vex.spotName >> vex.spotInfo;
		insertVexReslut = mGraph->insertVex(vex);
		if (!insertVexReslut)
			break;
	}
	InFile.close();
	if (!insertVexReslut)
	{
		cout << "���뾰��ʧ��!������Ϣ�����ƣ�" << endl;
		return false;
	}
	// ���ļ���ȡ����ߵ���Ϣ
	bool insertEdgeResult;
	Edge edge;
	InFile.open("edges.txt", ios::in);
	if (!InFile.is_open())
	{
		cout << "���ļ�edges.txtʧ�ܣ�" << endl;
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
		cout << "���뾰���ı�ʧ�ܣ�" << endl;
		return false;
	}
	// ��ʾͼ����Ϣ
	cout << "\n����ͼ�����ɹ�������������Ϣ����" << endl;
	mGraph->prinGraphInfo();
	return true;
}

void Tourism::querySpotInfo()
{
	int querynum; 
	Vex queryVex;
	Edge *qureyEdge=new Edge[MAX_SPOT_NUM];
	int Edgecount;
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	cin >> querynum;
	queryVex=mGraph->getVex(querynum);
	mGraph->printVex(queryVex);
	cout << "--------�ܱ߾���----------" << endl;
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
		cout << "��ϵͳ��û�ж��㣬����ͼ�Ƿ񴴽�" << endl;
		return;
	}
	cout << "----���ξ��㵼��----" << endl;
	mGraph->printNodeInfo();
	int beginVexIndex = -1;
	cout << "��������ʼ�����ı��:";
	cin >> beginVexIndex;
	if (beginVexIndex >= mGraph->getVexNum())
	{
		cout << "����ľ����������" << endl;
		return;
	}
	/*
	*���ɱ���·��
	*/
	PathList pathlist = new PathNode;
	PathList pathlistTail = pathlist;
	mGraph->DFSTravel(beginVexIndex, pathlistTail);
	/*
	*��ӡ·��
	*/
	cout << "����·��Ϊ:\n";
	int  routeCountNum = 0;
	while (pathlist->next != NULL)
	{
		cout << endl << "·��" << ++routeCountNum << ":" << endl;
		for (int icount = 0; icount < mGraph->getVexNum() - 1; icount++)
		{
			cout << (mGraph->getVex(pathlist->vexIndex[icount])).spotName<< "->";
		}
		cout << mGraph->getVex(pathlist->vexIndex[mGraph->getVexNum() - 1]).spotName << endl;
		pathlist = pathlist->next;//��һ��·��

	}

}

void Tourism::findShortPath()
{
	cout << endl << "-----�������·��-----" << endl;
	if (mGraph->getVexNum() == 0)
	{
		cout << "��ϵͳ��û�ж��㣬����ͼ�Ƿ񴴽�" << endl;
		return;
	}
	//������ֹ����
	mGraph->printNodeInfo();
	int vexStart, vexEnd;
	cout << "���������뿪ʼ��������ֹ����ı�ţ�";
	cin >> vexStart >> vexEnd;
	//����쳣�ж�
	if (vexStart >= mGraph->getVexNum() || vexEnd >= mGraph->getVexNum())
	{
		cout << "����ľ����������" << endl;
		return;
	}
	// path[i]��Ӧ�ŵϽ�˹�����㷨�����У���i����㵽Դ�����·���У�
	// ��һ����ת�����±꣨��ǰ����ǰ�����Լ���Դ�����̾���
	Edge path[MAX_SPOT_NUM];
	mGraph->findShortPath(vexStart, vexEnd, path);

	// �Ӻ���ǰ���� �˴�����һ��ջ�������
	stack<int> s;
	int index = vexEnd;
	while (1)
	{
		s.push(index);
		index = path[index].vex1;
		if (index == vexStart)
			break;
	}
	cout << "\n��̵�����·�����£�" << endl;
	cout << mGraph->getVex(vexStart).spotName;

	while (!s.empty())
	{
		cout << " ->" << mGraph->getVex(s.top()).spotName;
		s.pop();
	}
	cout << "    �ܳ� " << path[vexEnd].distance << " ��" << endl << endl;
}

void Tourism::designPath()
{
	if (mGraph->getVexNum() == 0)
	{
		cout << "��ǰͼ��û�ж��㣬�����Ƿ��Ѿ�����ͼ" << endl;
		return;
	}
	vector<Edge> edges = mGraph->findMinTree();
	int totalCost = 0;
	cout << "\n======���������������======\n";
	for (vector<Edge>::iterator iter = edges.begin(); iter != edges.end(); iter++)
	{
		cout << mGraph->getVex(iter->vex1).spotName << " -- " <<
			mGraph->getVex(iter->vex2).spotName << iter->distance << "��" << endl;

		totalCost += iter->distance;
	}
	cout << "��������ܳ���Ϊ��" << totalCost << "��" << endl << endl;
}
