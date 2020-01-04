#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <int> seq(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> seq[i];
	}
	//vector <vector<int>> dp(n + 1, vector <int>(n + 1, -100));
	//dp[0][0] = 0;
	vector <int> dp(n + 1);
	vector <int> par(n + 1, -1);
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		dp[i] = 1;
		for (int j = 1; j < i; j++)
		{
			if (seq[j] < seq[i])
			{
				//dp[i] = max(dp[i], dp[j] + 1);
				if (dp[j] + 1 > dp[i])
				{
					dp[i] = dp[j] + 1;
					par[i] = j;
				}
			}
		}
	}

	int answ = dp[1];
	int id = 1;
	for (int i = 2; i <= n; i++)
	{
		if (dp[i] > answ)
		{
			answ = dp[i];
			id = i;
		}
	}
	//cout << *max_element(dp.begin(), dp.end()) << '\n';
	cout << answ << '\n';
	vector <int> path;
	while (id != -1)
	{
		path.push_back(seq[id]);
		id = par[id];
	}
	reverse(path.begin(), path.end());
	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i] << ' ';
	}
	return 0;
}
