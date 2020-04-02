#pragma once
//左零右一
struct HTNode
{
	int weight;//权值
	struct HTNode * parent;//父亲节点
	struct HTNode * lchild;//左孩子
	struct HTNode * lchild;//右孩子
};
void str2byte();
void 