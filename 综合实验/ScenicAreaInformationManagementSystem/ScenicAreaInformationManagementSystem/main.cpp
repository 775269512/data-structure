#include<iostream>
#include"Tourism.h"
#include "graph.h"
using namespace std;
void showmanu();
int main()
{
	int choice = 0;
	Tourism *t=new Tourism();
	while(true)
	{ 
		showmanu();//GUI
		cin >> choice;
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			t->createGraph();
			break;
		case 2:
			t->querySpotInfo();
			break;
		case 3:
			t->travelPath();
			break;
		case 4:
			t->findShortPath();
			break;
		case 5:
			t->designPath();
			break;
		default:
			cout << "��������ȷ�Ĺ�����ţ�" << endl;
			break;
		}
	}

	return 0;
}
void showmanu()
{
	cout << endl << "=================��������ϵͳ=========================" << endl;
	cout << "1.��������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.�������·��" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�ϵͳ" << endl;
	cout << "�����������ţ�0~5��:";

}