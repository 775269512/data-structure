#include<stdlib.h>
#include<stdio.h>
struct item {
	float coef;
	int expn;
	struct item *next;
};
struct Node {
	int flag;
	struct Node *next;
};
void calcu();
void calculator();
void runysf(int n, struct Node *head);
void Yuesefu();
struct Node* initList(int m);
void polynomial_addition();
struct item *initPoly();
void printPoly(struct item *head);
struct item *addPoly(struct item * h1, struct item *h2);
struct item *subtractPoly(struct item * h1, struct item *h2);
