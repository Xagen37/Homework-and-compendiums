#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;
const int MOD = 1e9 + 7;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map<char, int> edges;
};

int main()
{
	freopen("problem4.in", "r", stdin);
	freopen("problem4.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m, k, l;
	cin >> n >> m >> k >> l;
	vector <Node> nodes(n + 1);
	for (int i = 1; i <= n; i++)
	{
		nodes[i].id = i;
	}
	for (int i = 0; i < k; i++)
	{
		int id;
		cin >> id;
		nodes[id].is_allowing = true;
	}
	for (int i = 0; i < m; i++)
	{
		int from, to; char c;
		cin >> from >> to >> c;
		nodes[from].edges[c] = to;
	}

	vector <vector <int>> dp(l + 1, vector <int>(n + 1, 0));
	dp[0][1] = 1;
	for (int i = 0; i < l; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			auto& automata = nodes[j].edges;
			for (auto nier : automata)
			{
				dp[i + 1][nier.second] = (dp[i + 1][nier.second] + dp[i][j]) % MOD;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i <= n; i++)
	{
		if (nodes[i].is_allowing)
		{
			sum = (sum + dp[l][i]) % MOD;
		}
	}
	cout << sum;

	return 0;
}