#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <int> cost(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> cost[i];
	}

	vector <vector <pair<int, int>>> dp(n + 1, vector <pair<int, int>>(n + 1, { 1e6, 0 }));
	vector <vector <pair<int, int>>> par(n + 1, vector <pair<int, int>>(n + 1, {-1, -1}));
	dp[0][0] = {0, 0};
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			/*if (!j)
			{
				if (cost[i] > 100)
				{

				}
				else
				{
					dp[i][j] = dp[i - 1][j];
					dp[i][j].first += cost[i];
					par[i][j] = { i - 1, j };
				}
			}*/
			if (cost[i] > 100)
			{
				if (!j || j < n && dp[i - 1][j - 1].first + cost[i] > dp[i - 1][j + 1].first)
				{
					dp[i][j].first = dp[i - 1][j + 1].first;
					dp[i][j].second = dp[i - 1][j + 1].second + 1;
					par[i][j] = { i - 1, j + 1 };
				}
				else
				{
					dp[i][j].first = dp[i - 1][j - 1].first + cost[i];
					dp[i][j].second = dp[i - 1][j - 1].second;
					par[i][j] = { i - 1, j - 1 };
				}
			}
			else
			{
				if (j < n && dp[i - 1][j].first + cost[i] > dp[i - 1][j + 1].first)
				{
					dp[i][j].first = dp[i - 1][j + 1].first;
					dp[i][j].second = dp[i - 1][j + 1].second + 1;
					par[i][j] = { i - 1, j + 1 };
				}
				else
				{
					dp[i][j].first = dp[i - 1][j].first + cost[i];
					dp[i][j].second = dp[i - 1][j].second;
					par[i][j] = { i - 1, j };
				}
			}
		}
	}

	int coup = -1, answ = 1e6, used = 0;
	for (int i = 0; i <= n; i++)
	{
		if (dp[n][i].first <= answ)
		{
			answ = dp[n][i].first;
			coup = i;
			used = dp[n][i].second;
		}
	}

	cout << answ << '\n' << coup << ' ' << used << '\n';
	vector <int> path;
	pair<int, int> u = { n, coup };
	while (u.first > 0)
	{
		if (u.second - par[u.first][u.second].second == -1)
		{
			path.push_back(u.first);
		}
		u = par[u.first][u.second];
	}
	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i] << '\n';
	}

	return 0;
}