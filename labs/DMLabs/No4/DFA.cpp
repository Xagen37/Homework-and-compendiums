#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map<char, int> edges;
};

int main()
{
	freopen("problem1.in", "r", stdin);
	freopen("problem1.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string word;
	cin >> word;
	int n, m, k;
	cin >> n >> m >> k;
	vector <Node> nodes(n + 1);
	for (int i = 1; i <= n; i++)
	{
		nodes[i].id = i;
	}
	for (int i = 0; i < k; i++)
	{
		int id;
		cin >> id;
		nodes[id].is_allowing = true;
	}
	for (int i = 0; i < m; i++)
	{
		int from, to; char c;
		cin >> from >> to >> c;
		nodes[from].edges[c] = to;
	}

	int curr = 1; bool flag = false;
	for (int i = 0; i < word.length(); i++)
	{
		if (nodes[curr].edges.find(word[i]) == nodes[curr].edges.end())
		{
			flag = true;
			break;
		}
		curr = nodes[curr].edges[word[i]];
	}

	if (!flag && nodes[curr].is_allowing)
	{
		cout << "Accepts";
	}
	else
	{
		cout << "Rejects";
	}

	return 0;
}
