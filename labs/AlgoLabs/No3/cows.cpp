#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	freopen("skyscraper.in", "r", stdin);
	freopen("skyscraper.out", "w", stdout);
	unsigned long long int n, w;
	cin >> n >> w;
	vector <unsigned long long int> cow(n);
	for (int i = 0; i < n; i++)
	{
		cin >> cow[i];
	}
	vector <pair<unsigned long long int, unsigned long long int>> dp(1 << n, {LONG_MAX, LONG_MAX});
	vector <vector <int>> path(1 << n);
	dp[0] = {0, 0};
	path[0] = {0};
	for (int x = 0; x < (1 << n); x++)
	{
		for (int i = 0; i < n; i++)
		{
			if (!(x & (1 << i)))
			{
				unsigned long long int f, s;
				vector <int> next;
				if (cow[i] + dp[x].second <= w)
				{
					f = dp[x].first;
					s = dp[x].second + cow[i];
					next = path[x];
				}
				else
				{
					f = dp[x].first + 1;
					s = cow[i];
					next = path[x];
				}

				if (dp[x | (1 << i)].first > f)
				{
					dp[x | (1 << i)].first = f;
					dp[x | (1 << i)].second = s;
					next.push_back(x | (1 << i));
					path[x | (1 << i)] = next;
				}
				else if (dp[x | (1 << i)].first == f && dp[x | (1 << i)].second > s)
				{
					dp[x | (1 << i)].first = f;
					dp[x | (1 << i)].second = s;
					next.push_back(x | (1 << i));
					path[x | (1 << i)] = next;
				}
				//dp[x | (1 << i)] = min(dp[x | (1 << i)], { f , s });
			}
		}
	}

	
	if (!dp[(1 << n) - 1].second)
	{
		cout << dp[(1 << n) - 1].first << '\n';
	}
	else
	{
		cout << dp[(1 << n) - 1].first + 1 << '\n';
	}
	/*for (int i = 0; i < path[(1 << n) - 1].size(); i++)
	{
		cout << path[(1 << n) - 1][i] << ' ';
	}
	cout << endl;*/
	vector <vector <int>> answ;
	vector <int> temp;
	for (int i = 0; i < path[(1 << n) - 1].size() - 1; i++)
	{
			if (dp[path[(1 << n) - 1][i + 1]].first == dp[path[(1 << n) - 1][i]].first)
			{
				int c = path[(1 << n) - 1][i + 1] - path[(1 << n) - 1][i];
				int cnt = 0;
				while (!(c & (1 << cnt)))
				{
					cnt++;
				}
				temp.push_back(cnt + 1);
			}
			else
			{
				answ.push_back(temp);
				temp.clear();
				int c = path[(1 << n) - 1][i + 1] - path[(1 << n) - 1][i];
				int cnt = 0;
				while (!(c & (1 << cnt)))
				{
					cnt++;
				}
				temp.push_back(cnt + 1);
				//temp.push_back(path[(1 << n) - 1][i + 1] - path[(1 << n) - 1][i]);
			}
	}
	if (!temp.empty())
	{
		answ.push_back(temp);
	}
	
	for (int i = 0; i < answ.size(); i++)
	{
		cout << answ[i].size() << ' ';
		for (int j = 0; j < answ[i].size(); j++)
		{
			cout << answ[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}