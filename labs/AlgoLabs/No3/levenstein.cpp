#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string first, second;
	cin >> first >> second;
	unsigned int n = second.length();
	unsigned int m = first.length();
	vector <vector <int> > dp(n + 1, vector <int>(m + 1, 0));

	for (int i = 0; i < m + 1; i++)
	{
		dp[0][i] = i;
	}
	for (int i = 0; i < n + 1; i++)
	{
		dp[i][0] = i;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (second[i - 1] == first[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = min(min(dp[i - 1][j - 1], dp[i][j - 1]), dp[i - 1][j]) + 1;
			}
		}
	}

	cout << dp[n][m];
	return 0;
}