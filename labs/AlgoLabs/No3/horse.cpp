#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	const int MOD = 1e9;
	int n;
	cin >> n;
	int map[][3] =
	{
		{-1, 4, 6},
		{-1, 6, 8}, {-1, 7, 9}, {-1, 8, 4},
		{0, 3, 9}, {-1, -1, -1}, {0, 1, 7},
		{-1, 2, 6}, {-1, 1, 3}, {-1, 2, 4}
	};
	vector <vector <int>> dp(10, vector <int>(n + 1, 0));
	for (int i = 0; i < 10; i++)
	{
		if (i != 0 && i != 8)
		{
			dp[i][1] = 1;
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (map[j][k] != -1)
				{
					dp[map[j][k]][i + 1] += dp[j][i];
					dp[map[j][k]][i + 1] %= MOD;
				}
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum = (sum + dp[i][n]) % MOD;
	}
	cout << sum;
	return 0;
}