#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	long long int n;
	cin >> n;
	vector <vector <long long int> > road(n, vector <long long int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> road[i][j];
		}
	}
	
	vector <vector <long long int>> dp(1 << n, vector <long long int>(n, INT_MAX - 1000));
	vector <vector <pair <int, int>>> par(1 << n, vector <pair <int, int>>(n, {0, -1}));
	dp[0].assign(n, 0);
	for (int i = 0; i < n; i++)
	{
		dp[1 << i][i] = 0;
	}
	for (int i = 0; i < (1 << n); i++)
	{
		for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!(i & (1 << j)))
				{
					if (dp[i | (1 << j)][j] > dp[i][k] + road[k][j])
					{
						dp[i | (1 << j)][j] = dp[i][k] + road[k][j];
						par[i | (1 << j)][j] = { i, k };
					}
					//dp[i | (1 << j)][j] = min(dp[i | (1 << j)][j], dp[i][k] + road[k][j]);
				}
			}
		}
	}
	
	long long int answ = LONG_MAX;
	int id = -1;
	for (int i = 0; i < n; i++)
	{
		if (dp[(1 << n) - 1][i] < answ)
		{
			answ = dp[(1 << n) - 1][i];
			id = i;
		}
	}
	cout << answ << '\n';

	/*for (int i = 0; i < (1 << n); i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << dp[i][k] << ' ';
		}
		cout << endl;
	}*/
	vector <int> path;
	long long int mask = ((1LL << n) - 1);
	while (mask)
	{
		path.push_back(id + 1);
		long long int n_mask = par[mask][id].first;
		int n_id = par[mask][id].second;
		mask = n_mask;
		id = n_id;
	}
	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i] << ' ';
	}
	
	return 0;
}