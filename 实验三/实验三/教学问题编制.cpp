#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MaxVertices 100
#define MaxStackSize 100
#define numterm 8
#define uplcredit 10
#define Notstudy	0
#define study		1

typedef int DataType;

#include "Stack.h"
#include "GreatGraph.h"
#include "Topologicalsort.h" 
#include "FindIndegree.h"

void main()
{
	int numterm;          //学期总数
	int uplcredit;        //一个学期的学分上限
	char name[12][9]={"程序设计","离散数学","数据结构","汇编语言","语言的设计和分析","计算机原理","编译原理","操作系统","高等数学","线性代数","普通物理","数值分析"}；
	int number[12]={2,3,4,3,2,3,4,4,7,5,2,3};
    int RC[15][2]={{1,2},{1,4},{1,12},{2,3},{3,5},{3,7},{3,8},{4,5},{5,7},{6,8},{9,10},{9,11},{9,12},{10,12},{11,6}};
	int b=15,a=12;

	SeqStack s;
	ALGraph G;            //图G变量
	printf("学期总数：%d\n",numterm);
	printf("学期的学分上限：%d\n",uplcredit);
	GreatGraph(&G,name,number,a,b,RC);        //创建一个图
	printf("请选择编排策略：1.课程尽可能集中到前几个学期；2.课程尽量均匀分布\n");
	scanf("%d",&selectway);
	Topologicalsort(G,numterm,uplcredit);//执行教学课程编排
}


