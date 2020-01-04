#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, k;
	cin >> n >> k;
	vector <int> coin(n + 1, 0);
	for (int i = 2; i < n; i++)
	{
		cin >> coin[i];
	}
	vector <int> dp(n + 1, INT_MIN);
	vector <int> par(n + 1, -1);
	dp[0] = INT_MIN;
	dp[1] = 0;
	par[1] = -1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if ((i - j) > 0)
			{
				if (dp[i] < dp[i - j] + coin[i])
				{
					dp[i] = dp[i - j] + coin[i];
					par[i] = i - j;
				}
			}
			else
			{
				break;
			}
		}
	}
	coin.clear();
	cout << dp[n] << '\n';
	dp.clear();
	vector <int> path;
	while (n != -1)
	{
		path.push_back(n);
		n = par[n];
	}
	if (path.back() != 1)
	{
		if (path.back() < 1)
		{
			path.pop_back();
		}
		path.push_back(1);
	}
	//path.push_back(1);
	cout << path.size() - 1 << '\n';
	//reverse(path.begin(), path.end());
	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i] << ' ';
	}
	return 0;
}