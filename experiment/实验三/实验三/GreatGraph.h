typedef struct TeaNode
{
	int adjvex;                       //��ͷ������
	struct TeaNode *next;             //���������һ�����ָ��
}TeaNode;                             //����Ľ��
typedef struct
{
	char name[30];                    //�γ�����
	int code;                         //�γ̱��
	int credit;                       //�γ�ѧ��
	int indegree;                     //�γ����
	int state;                        //�ýڵ��״̬
	TeaNode *firstTea;                //�ڽӱߵ�ͷָ��
}NumNode;                             //ͷ���
typedef struct
{
	NumNode vertices[MaxVertices];    //�ڽӱ�����
	int vexnum;                       //������
	int	arcnum;                       //����
}ALGraph;                             //�ڽӱ�ṹ��

typedef struct//����Ϣ�ṹ��
{
	int row;
	int col;
}RowCol;                              
void ALInitiate(ALGraph *G)//��ʼ��ͼG
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
void InsertVertex(ALGraph *G,int i,char a,int d)//���붥��
{
	if(i>=0&&i<MaxVertices)
	{
		G->vertices[i].name[30]=a;
		G->vertices[i].credit=d;
		G->vexnum++;
	}
	else
		printf("����Խ��");
}                                      
void InsertEdge(ALGraph *G,int v1,int v2)//�����
{
	TeaNode *p;
	if(v1<0||v1>=G->vexnum||v2<0||v2>G->vexnum)
	{
		printf("����v1��v2Խ�����");
		return;
	}
	p=(TeaNode*)malloc(sizeof(TeaNode));
	p->adjvex=v2;
	p->next=G->vertices[v1].firstTea;
	G->vertices[v1].firstTea=p;
	G->arcnum++;
}                                        
void CreatGraph(ALGraph *G, char *n[],int *m[],int num,int e,RowCol o[])//����һ��ͼG
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