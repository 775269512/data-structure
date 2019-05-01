typedef struct TeaNode
{
	int adjvex;                       //弧头结点序号
	struct TeaNode *next;             //单链表的下一个结点指针
}TeaNode;                             //链表的结点
typedef struct
{
	char name[30];                    //课程名称
	int code;                         //课程编号
	int credit;                       //课程学分
	int indegree;                     //课程入度
	int state;                        //该节点的状态
	TeaNode *firstTea;                //邻接边的头指针
}NumNode;                             //头结点
typedef struct
{
	NumNode vertices[MaxVertices];    //邻接表数组
	int vexnum;                       //顶点数
	int	arcnum;                       //弧数
}ALGraph;                             //邻接表结构体

typedef struct//边信息结构体
{
	int row;
	int col;
}RowCol;                              
void ALInitiate(ALGraph *G)//初始化图G
{
	int i;
	G->vexnum=0;
	G->arcnum=0;
	for(i=0;i<MaxVertices;i++)
	{
		if(i<10)
		G->vertices[i].code=i;
		if(i>=10)
		G->vertices[i].code=i;
		G->vertices[i].firstTea=NULL;
		G->vertices[i].indegree=0;
		G->vertices[i].state=Notstudy;
	}
}                                       
void InsertVertex(ALGraph *G,int i,char a,int d)//插入顶点
{
	if(i>=0&&i<MaxVertices)
	{
		G->vertices[i].name[30]=a;
		G->vertices[i].credit=d;
		G->vexnum++;
	}
	else
		printf("顶点越界");
}                                      
void InsertEdge(ALGraph *G,int v1,int v2)//插入边
{
	TeaNode *p;
	if(v1<0||v1>=G->vexnum||v2<0||v2>G->vexnum)
	{
		printf("参数v1或v2越界出错！");
		return;
	}
	p=(TeaNode*)malloc(sizeof(TeaNode));
	p->adjvex=v2;
	p->next=G->vertices[v1].firstTea;
	G->vertices[v1].firstTea=p;
	G->arcnum++;
}                                        
void CreatGraph(ALGraph *G, char *n[],int *m[],int num,int e,RowCol o[])//构建一个图G
{
	int i,k;
	ALInitiate(G);
	for(i=0;i<num;i++)
		InsertVertex(G,i,n[i],m[i]);
	for(k=0;k<e;k++)
		InsertEdge(G,o[k].row,o[k].col);
}                                       
void FindInDegree(ALGraph G, int indegree[]);
void Topologicalsort(ALGraph G, int numterm, int uplcredit);