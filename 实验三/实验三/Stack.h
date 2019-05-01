#define DataType int;
#define MaxStackSize 100;
typedef struct
{
	DataType stack[MaxStackSize];
	int stacks[100];
	int top;
}SeqStack;                               //定义一个叫SeqStack的结构体
void StackInitiate(SeqStack *S)
{
	S->top=0;
}                                        //初始化堆栈
int StackNotEmpty(SeqStack S)
{
	if(S.top<=0)
		return 0;
	else
		return 1;
}                                       //判断堆栈是否为空
int StackPush(SeqStack *S,DataType x)
{
	if(S->top>=MaxStackSize)
	{
		printf("堆栈已满无法插入！\n");
		return 0;
	}
	else
	{
		S->stack[S->top]=x;
		S->top++;
		return 1;
	}
}                                     //将要入栈的元素进行入栈
int StackPop(SeqStack *S,DataType *d)
{
	if(S->top<=0)
	{
		printf("堆栈已空无数据元素出栈！\n");
		return 0;
	}
	else
	{
		S->top--;
		*d=S->stack[S->top];
		return 1;
	}
}                                     //将要出栈的元素进行出栈
