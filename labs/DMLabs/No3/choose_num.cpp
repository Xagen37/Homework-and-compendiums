#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;
int n, k;
vector <vector <long long int>> c;
int build(vector <int>& in)
{
	int num = 0;
	for (int i = 1; i <= k; i++)
	{
		for (int j = in[i - 1] + 1; j < in[i]; j++)
		{
			num += c[n - j][k - i];
		}
	}
	return num;
}

int main()
{
	freopen("choose2num.in", "r", stdin);
	freopen("choose2num.out", "w", stdout);

	cin >> n >> k;
	vector <int> in(k + 1, 0);
	for (int i = 1; i <= k; i++)
	{
		cin >> in[i];
	}
	c.resize(n, vector <long long int>(k, 0));
	for (int i = 0; i < n; i++)
	{
		c[i][0] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < k; j++)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
	cout << build(in);
	return 0;
}
