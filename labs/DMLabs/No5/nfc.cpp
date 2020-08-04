#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int main()
{
	freopen("nfc.in", "r", stdin);
	freopen("nfc.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	constexpr int MOD = 1000000007;
	int n; cin >> n;
	char start; cin >> start;
	unordered_map<char, vector <string>> rules;
	unordered_set<char> non_ters;
	non_ters.insert(start);
	for (int i = 0; i < n; i++)
	{
		char non_ter; cin >> non_ter;
		non_ters.insert(non_ter);
		string arrow; cin >> arrow;
		string result; cin >> result;
		rules[non_ter].push_back(result);
		if (result.size() == 2)
		{
			non_ters.insert(result[0]);
			non_ters.insert(result[1]);
		}
	}
	string word; cin >> word;
	unordered_map<char, vector <vector <long long int>>> dp;
	for (char it : non_ters)
	{
		dp.emplace(it, vector <vector <long long int>>(word.size(), vector<long long int>(word.size(), 0)));
	}

	for (int i = 0; i < word.size(); i++)
	{
		for (auto& it : dp)
		{
			vector <string>& copy = rules[it.first];
			for (auto& str : copy)
			{
				if (str.size() == 1)
				{
					if (word[i] == str[0])
					{
						dp[it.first][i][i]++;
					}
				}
			}
		}
	}

	for (int m = 1; m < word.size(); m++)
	{
		for (int i = 0, j = i + m; i < word.size() - m; i++, j++)
		{
			for (auto& it : dp)
			{
				vector <string>& copy = rules[it.first];
				for (auto& str : copy)
				{
					if (str.size() == 2)
					{
						for (int k = i; k < j; k++)
						{
							dp[it.first][i][j] = (dp[it.first][i][j] + (dp[str[0]][i][k] * dp[str[1]][k + 1][j]) % MOD) % MOD;
						}
					}
				}
			}
		}
	}

	cout << dp[start][0][word.size() - 1];

	return 0;
}
