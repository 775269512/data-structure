#pragma once
#include"graph.h"
#include<iostream>
class Tourism
{
private:
	Graph *mGraph;  //图信息指针
public:
	Tourism();
	~Tourism();
	bool createGraph();				//创建景点图
	void querySpotInfo();			//查询景点信息
	void travelPath();				//旅游景点导航
	void findShortPath();			//搜索最短路径
	void designPath();				//铺设电路规划

};