#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
vector <vector <long long int>> c;
vector <int> build()
{
	vector<int> answ;
	int next = 1;
	while (k)
	{
		if (m < c[n - 1][k - 1])
		{
			answ.push_back(next);
			k--;
		}
		else
		{
			m -= c[n - 1][k - 1];
		}
		n--;
		next++;
	}
	return answ;
}
int main()
{
	freopen("num2choose.in", "r", stdin);
	freopen("num2choose.out", "w", stdout);

	cin >> n >> k >> m;
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

	vector <int> a = build();
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << ' ';
	}

	return 0;
}