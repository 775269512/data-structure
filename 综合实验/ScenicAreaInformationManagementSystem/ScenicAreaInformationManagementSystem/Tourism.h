#pragma once
#include"graph.h"
#include<iostream>
class Tourism
{
private:
	Graph *mGraph;  //ͼ��Ϣָ��
public:
	Tourism();
	~Tourism();
	bool createGraph();				//��������ͼ
	void querySpotInfo();			//��ѯ������Ϣ
	void travelPath();				//���ξ��㵼��
	void findShortPath();			//�������·��
	void designPath();				//�����·�滮

};