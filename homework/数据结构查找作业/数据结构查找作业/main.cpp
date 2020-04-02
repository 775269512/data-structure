#include <iostream>
using namespace std;
int Binary_Search(int *a, int start,int end,int key)
{
	int mid = (end + start) / 2 ;
	if (a[mid] == key)
		return mid;
	//if (a[start] == key)	return start;
	//if (a[end] == key)return end;
	if (end < start)
		return -1;
	if (a[mid]>=key)
	{
		return Binary_Search(a, start, mid-1, key);
	}
	if(a[mid]<=key)
		return Binary_Search(a, mid+1, end , key);
	return -1;
}
int Binary_Search(int *a, int len, int key)
{
	int low = 0;
	int hei = len;
	if(a[low] == key)return low;
	//if (a[hei] == key)return hei;
	while (low <= hei)
	{
		int mid = (low + hei) / 2;
		if (a[mid] == key) return mid;
		if (a[mid] > key) hei = mid -1 ;
		if (a[mid] < key)  low = mid + 1;

	}
	return -1;
}
int main()
{
	//²âÊÔº¯ÊıÖØÔØ
	int n = 100;
	int i = 0;
	int *a=new int[n];
	for (i; i < n; i++)
		a[i] = i;
	i = 0;
	for (i; i < n; i++)
	{
		cout << Binary_Search(a, 0, n-1, i) << endl;
		cout << Binary_Search(a, n-1, i) << endl;
	}
	return 0;
}