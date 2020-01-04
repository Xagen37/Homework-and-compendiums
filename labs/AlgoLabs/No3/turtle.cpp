#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector < vector <int>> dp(n + 1, vector <int>(m + 1, -100));
	vector <vector <int>> coin(n + 1, vector <int>(m + 1, 0));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> coin[i][j];
		}
	}
	dp[1][1] =  coin[1][1];
	vector <vector <pair<int, int>>> par(n + 1, vector <pair<int, int>>(m + 1, {-1, -1}));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (dp[i][j] < dp[i][j - 1] + coin[i][j])
			{
				//cerr << i << ' ' << j << 'R' << endl;
				dp[i][j] = dp[i][j - 1] + coin[i][j];
				par[i][j] = { i, j - 1 };
				/*dp[i][j].first = dp[i][j - 1].first + coin[i][j];
				dp[i][j].second = dp[i][j - 1].second + "R";*/
			}
			if (dp[i][j] < dp[i - 1][j] + coin[i][j])
			{
				/*dp[i][j].first = dp[i - 1][j].first + coin[i][j];
				dp[i][j].second = dp[i - 1][j].second + "D";*/
				//cerr << i << ' ' << j << 'D' << endl;
				dp[i][j] = dp[i - 1][j] + coin[i][j];
				par[i][j] = { i - 1, j };
			}
		}
	}
	cout << dp[n][m] << '\n';
	string path = "";
	pair<int, int> a = { n, m };
	while (a != make_pair(-1, -1))
	{
		if (par[a.first][a.second] == make_pair(a.first - 1, a.second))
		{
			a.first--;
			path.append("D");
		}
		else if (par[a.first][a.second] == make_pair(a.first, a.second - 1))
		{
			a.second--;
			path.append("R");
		}
		else
		{
			a = { -1, -1 };
		}
	}
	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i];
	}
	return 0;
}