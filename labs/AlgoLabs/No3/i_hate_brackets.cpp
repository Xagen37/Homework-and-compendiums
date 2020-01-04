#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;
string s;
vector <vector <int> > dp;
vector <vector <int> > best_k;
unordered_map <char, char> acc;

void answ(int left, int right)
{
	if (dp[left][right] == right - left + 1)
	{
		return;
	}
	if (dp[left][right] == 0)
	{
		cout << s.substr(left, right - left + 1);
		return;
	}
	if (best_k[left][right] == -1)
	{
		cout << s[left];
		answ(left + 1, right - 1);
		cout << s[right];
		return;
	}

	answ(left, best_k[left][right]);
	answ(best_k[left][right] + 1, right);
}

int main()
{
	cin >> s;
	int n = s.length();
	if (!n)
	{
		cout << "";
		return 0;
	}
	dp.resize(n, vector<int>(n, 0));  //[i, j] - substr
	best_k.resize(n, vector<int>(n, -1));
	acc =
	{
		{'(', ')' },
		{'[', ']' },
		{'{', '}' }
	};
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i > j)
			{
				dp[i][j] = 0;
			}
		}
	}*/
	for (int i = 0; i < n; i++)
	{
		dp[i][i] = 1;
	}

	for (int j = 0; j < n; j++)
	{
		for (int i = j - 1; i >= 0; i--)
		{
			int mi = 1e6;
			if (acc.count(s[i]) && acc.at(s[i]) == s[j])
			{
				mi = dp[i + 1][j - 1];
			}
		
			for (int k = i; k < j; k++)
			{
				if (mi > dp[i][k] + dp[k + 1][j])
				{
					mi = dp[i][k] + dp[k + 1][j];
					best_k[i][j] = k;
				}
				//mi = min(mi, dp[i][k] + dp[k + 1][j]);
			}
			dp[i][j] = mi;
			
		}
	}

	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << dp[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << dp[0][n - 1] << endl;*/

	answ(0, n - 1);

	return 0;
}
