#include <iostream>
#include <vector>

using namespace std;
int main()
{
	int n, m;
	cin >> n >> m;
	vector <vector <bool>> field(n + 1, vector <bool>(m + 1, 1));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char c;
			cin >> c;
			if (c == '.')
			{
				field[i][j] = 0;
			}
			else if (c == 'X')
			{
				field[i][j] = 1;
			}
		}
	}

	vector <vector <vector<long long int>>> dp(n + 1, vector <vector <long long int>>(m + 1, vector <long long int>(1 << m, 0)));
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int p = 0; p < (1 << m); p++)
			{
				if (p & (1 << j) || field[i][j])
				{
					if (!(p & (1 << j)))
					{
						dp[i][j + 1][p] += dp[i][j][p];
					}
					else
					{
						dp[i][j + 1][p - (1 << j)] += dp[i][j][p];
					}
				}
				else
				{
					if (!field[i + 1][j])
					{
						dp[i][j + 1][p + (1 << j)] += dp[i][j][p];
					}
					if (/*j < (m - 1) && */!(p & (1 << (j + 1))) && !field[i][j + 1])
					{
						dp[i][j + 1][p + (1 << (j + 1))] += dp[i][j][p];
					}
				}
			}
		}
		for (int p = 0; p < (1 << m); p++)
		{
			dp[i + 1][0][p] = dp[i][m][p];
		}
	}

	/*for (int p = 0; p < (1 << m); p++)
	{
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				cout << dp[i][j][p] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}*/

	cout << dp[n][0][0];
	
	return 0;
}