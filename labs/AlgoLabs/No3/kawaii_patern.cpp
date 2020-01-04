#include <iostream>
#include <vector>

using namespace std;

int main()
{
	unsigned long long int n, m;
	cin >> n >> m;
	if (n < m)
	{
		swap(n, m);
	}
	vector <vector <bool>> check((1LL << m), vector <bool>((1LL << m), 1));

	for (unsigned long long int i = 0; i < (1LL << m); i++)
	{
		for (unsigned long long int j = 0; j < (1LL << m); j++)
		{
			for (int p = 0; p < (m - 1); p++)
			{
				int b1 = (i & (1LL << p));
				int b2 = (i & (1LL << (p + 1)));
				int b3 = (j & (1LL << p));
				int b4 = (j & (1LL << (p + 1)));
				if (b1 && b2 && b3 && b4)
				{
					check[i][j] = 0;
					break;
				}
				else if (!b1 && !b2 && !b3 && !b4)
				{
					check[i][j] = 0;
					break;
				}
				
			}
		}
	}

	vector <vector <unsigned long long int>> dp(n, vector <unsigned long long int>((1LL << m), 0));
	for (unsigned long long int i = 0; i < (1LL << m); i++)
	{
		dp[0][i] = 1;
	}

	for (unsigned long long int i = 1; i < n; i++)
	{
		for (unsigned long long int j = 0; j < (1LL << m); j++)
		{
			for (unsigned long long int p = 0; p < (1LL << m); p++)
			{
				dp[i][j] += dp[i - 1][p] * (int)check[p][j];
			}
		}
	}
	unsigned long long int answ = 0;
	for (unsigned long long int i = 0; i < (1LL << m); i++)
	{
		answ += dp[n - 1][i];
	}
	cout << answ;

	return 0;
}
