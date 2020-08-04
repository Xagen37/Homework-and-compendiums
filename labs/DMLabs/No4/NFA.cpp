#include <vector>
#include <cstdio>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map <char, vector <int>> edges;
};

int main()
{
	freopen("problem2.in", "r", stdin);
	freopen("problem2.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string word; cin >> word;
	int n, m, k; cin >> n >> m >> k;
	vector <Node> nodes(n + 1);
	for (int i = 1; i <= n; i++)
	{
		nodes[i].id = i;
	}
	for (int i = 0; i < k; i++)
	{
		int num; cin >> num;
		nodes[num].is_allowing = true;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b; char c;
		cin >> a >> b >> c;
		if (nodes[a].edges.find(c) == nodes[a].edges.end())
		{
			nodes[a].edges[c] = vector <int>({ b });
		}
		else
		{
			nodes[a].edges[c].push_back(b);
		}
	}

	bool flag = false;
	set <int> curr_set, next_set;
	curr_set.insert(1);
	for (int i = 0; i < word.length(); i++)
	{
		for (int idx : curr_set)
		{
			auto copy = nodes[idx].edges;
			if (copy.find(word[i]) != copy.end())
			{
				auto vector_copy = copy[word[i]];
				for (int j = 0; j < vector_copy.size(); j++)
				{
					next_set.insert(vector_copy[j]);
				}
			}
		}
		curr_set = next_set;
		next_set.clear();
	}

	for (auto it = curr_set.begin(); it != curr_set.end(); it++)
	{
		if (nodes[*it].is_allowing)
		{
			cout << "Accepts";
			return 0;
		}
	}
	cout << "Rejects";

	return 0;
}