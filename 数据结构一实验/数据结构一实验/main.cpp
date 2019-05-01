#include<stdio.h>
#include<stdlib.h>
#include"model.h"
int main()
{
	printf("\n问题一\n");
	Yuesefu();
	printf("\n问题二\n");
	polynomial_addition();
	printf("\n问题三\n输入计算式（以=结束）\n");
	calculator();

	system("pause");
	return 0;
}