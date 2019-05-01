#include <iostream>
#include <algorithm>
using namespace std;
const int MAX = 1000001;
int n, k, num[MAX], temp, sum;
int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	sort(num, num + n);
	sum = 1;
	for (int i = 0, temp = num[0]; i < n; i++)
	{
		if (num[i] - temp > k)
		{
			temp = num[i];
			sum++;
		}
		
	}
	cout << sum << endl;
	return 0;
}