#define DataType int;
#define MaxStackSize 100;
typedef struct
{
	DataType stack[MaxStackSize];
	int stacks[100];
	int top;
}SeqStack;                               //����һ����SeqStack�Ľṹ��
void StackInitiate(SeqStack *S)
{
	S->top=0;
}                                        //��ʼ����ջ
int StackNotEmpty(SeqStack S)
{
	if(S.top<=0)
		return 0;
	else
		return 1;
}                                       //�ж϶�ջ�Ƿ�Ϊ��
int StackPush(SeqStack *S,DataType x)
{
	if(S->top>=MaxStackSize)
	{
		printf("��ջ�����޷����룡\n");
		return 0;
	}
	else
	{
		S->stack[S->top]=x;
		S->top++;
		return 1;
	}
}                                     //��Ҫ��ջ��Ԫ�ؽ�����ջ
int StackPop(SeqStack *S,DataType *d)
{
	if(S->top<=0)
	{
		printf("��ջ�ѿ�������Ԫ�س�ջ��\n");
		return 0;
	}
	else
	{
		S->top--;
		*d=S->stack[S->top];
		return 1;
	}
}                                     //��Ҫ��ջ��Ԫ�ؽ��г�ջ
