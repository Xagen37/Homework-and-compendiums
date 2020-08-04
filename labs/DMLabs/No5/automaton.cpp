#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <queue>
#include <vector>
#include <set>

using namespace std;

bool check_word(map<char, vector<string>>& rules, char start, string word)
{
	bool flag = false;
	set<char> curr_set, next_set;
	curr_set.insert(start);
	for (int i = 0; i < word.length(); i++)
	{
		if (curr_set.empty()) { return false; }
		for (char non_ter : curr_set)
		{
			auto& copy = rules[non_ter];
			for (auto& res : copy)
			{
				if (res.length() == 1)
				{
					if (res[0] == word[i] && i == word.length() - 1)
					{
						flag = true;
					}
				}
				else
				{
					if (res[0] == word[i])
					{
						next_set.insert(res[1]);
					}
				}
			}
		}
		curr_set = next_set;
		next_set.clear();
	}
	if (!flag) 
	{ 
		return false; 
	}
	else
	{
		return true;
	}
}

int main()
{
	freopen("automaton.in", "r", stdin);
	freopen("automaton.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n; cin >> n;
	char start; cin >> start;

	map<char, vector<string>> rules;
	for (int i = 0; i < n; i++)
	{
		char non_ter; cin >> non_ter;
		string arrow; cin >> arrow;
		string result; cin >> result;
		rules[non_ter].push_back(result);
	}
	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		string word; cin >> word;
		if (check_word(rules, start, word))
		{
			cout << "yes\n";
		}
		else
		{
			cout << "no\n";
		}
	}
	return 0;
}
