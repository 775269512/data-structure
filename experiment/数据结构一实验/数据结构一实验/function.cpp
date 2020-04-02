
#include<stdio.h>
#include"model.h"
#pragma warning(disable:4996);

#define n0 30
double s1[n0 + 1];
char s2[n0 + 1];
int  t1, t2;
void calcu()
{
	double x1, x2, x;
	char p;
	p = s2[t2--];
	x2 = s1[t1--];
	x1 = s1[t1--];
	switch (p)
	{
	case'+': x = x1 + x2; break;
	case'-': x = x1 - x2; break;
	case'*': x = x1 * x2; break;
	case'/': x = x1 / x2;
	}
	s1[++t1] = x;
}
void calculator() {
	char c; double v;
	t1 = t2 = 0;
	scanf("%c", &c);
	while (c != '=')
		switch (c)
		{
		case'+': case'-':
			while (t2 && (s2[t2] != '('))
				calcu();
			s2[++t2] = c;
			scanf("%c", &c);
			break;
		case'*': case'/':
			if (t2 && ((s2[t2] == '*')) || (s2[t2] == '/'))
				calcu();
			s2[++t2] = c;
			scanf("%c", &c);
			break;
		case '(':case '（':
			s2[++t2] = c;
			scanf("%c", &c);
			break;
		case ')':case '）':
			while (s2[t2] != '(')
				calcu();
			t2--;
			scanf("%c", &c);
			break;
		case '\n':case ' ':case'  ':
			scanf("%c", &c);
			break;
		default:
			v = 0;
			do
			{
				v = 10 * v + c - '0';
				scanf("%c", &c);
			} while ((c >= '0') && (c <= '9'));
			s1[++t1] = v;
		};

	while (t2)
	calcu();
	printf("%lf", s1[t1]);
}
void runysf(int n, struct Node *head) {
	int i = 1;
	struct Node *ptr = head, *ptr1 = head->next;
	while (head->next != head) {
		if (i % n == 0) {
			printf("%d ", ptr1->flag);
			ptr->next = ptr1->next;
			free(ptr1);
			ptr1 = ptr->next;
		}
		else {
			ptr1 = ptr1->next;
			ptr = ptr->next;
		}
		i++;
		if (ptr1 == head)
		{
			ptr1 = ptr1->next;
			ptr = ptr->next;
		}
	}
}
void Yuesefu()
{
	int m, n;
	struct Node *head;
	printf("输入总人数m，以及循环数n：");
	scanf_s("%d%d", &m, &n);
	head = initList(m);
	runysf(n, head);


}
struct Node* initList(int m) {
	struct Node *head, *ptr, *ptr1;
	head = (struct Node *)malloc(sizeof(struct Node));
	ptr1 = head;
	for (int i = 0; i < m; i++) {
		ptr = (struct Node *)malloc(sizeof(struct Node));
		ptr->flag = i + 1;
		ptr1->next = ptr;
		ptr1 = ptr;
	}
	ptr1->next = head;

	return head;
}
void polynomial_addition() {
	struct item *headA, *headB, *headC, *headD, *headE, *headF;
	printf("多项式相加\n");
	printf("第一项多项式项数:");
	headA = initPoly();
	printf("第二项多项式项数:");
	headB = initPoly();

	printPoly(headA);

	printf("\n");

	printPoly(headB);

	printf("\n");

	headC = addPoly(headA, headB);
	printPoly(headC);

	printf("\n");
	printf("多项式相减\n");
	printf("第一项多项式项数:");
	headE = initPoly();
	printf("第二项多项式项数:");
	headF = initPoly();

	headD = subtractPoly(headE, headF);
	printPoly(headD);
}

struct item *initPoly() {
	int num;
	struct item *head = (struct item *)malloc(sizeof(struct item)), *ptr = head, *ptr1;

	scanf_s("%d", &num);

	for (int i = 0; i < num; i++) {
		ptr1 = (struct item *)malloc(sizeof(struct item));
		printf("请输入第%d项系数，指数：", i + 1);
		scanf_s("%f%d", &ptr1->coef, &ptr1->expn);
		ptr->next = ptr1;
		ptr = ptr->next;
	}
	ptr->next = NULL;

	return head;
}

void printPoly(struct item *head) {
	struct item *ptr = head->next;
	while (ptr != NULL) {
		if (ptr->next != NULL) {
			printf("%f*x^%d+", ptr->coef, ptr->expn);
		}
		else {
			printf("%f*x^%d", ptr->coef, ptr->expn);
		}
		ptr = ptr->next;
	}
}

struct item *addPoly(struct item * h1, struct item *h2) {
	struct item *head = h1, *pa = h1->next, *pb = h2->next;
	struct item *ppa = h1, *pc;
	while (pa != NULL && pb != NULL) {
		if (pa->expn < pb->expn) {
			ppa = ppa->next;
			pa = pa->next;
		}
		else if (pa->expn > pb->expn) {
			ppa->next = pb;
			pb = pb->next;
			ppa->next->next = pa;
			ppa = ppa->next;
		}
		else {
			if (pa->coef + pb->coef == 0)
			{
				pc = pb;
				pb = pb->next;
				free(pc);
				pc = pa;
				pa = pa->next;
				ppa->next = pa;
				free(pc);
			}
			else
			{
				pa->coef = pa->coef + pb->coef;
				pc = pb;
				pb = pb->next;
				free(pc);
			}
		}
	}
	if (pb != NULL) {
		ppa->next = pb;
	}

	return head;
}

struct item *subtractPoly(struct item * h1, struct item *h2) {
	struct item *ptr = h2->next;
	while (ptr != NULL) {
		ptr->coef = -ptr->coef;
		ptr = ptr->next;
	}

	ptr = addPoly(h1, h2);

	return ptr;
}
