#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <iostream>

using namespace std;
const int MOD = 1e9 + 7;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map<char, int> edges;
};

struct Non_det_node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map <char, vector <int>> edges;
};

vector <Node> tompson(vector <Non_det_node> & nodes)
{
	map <set<int>, int> new_q;
	new_q.insert({ set<int>({ 1 }), 1 });
	vector <Node> dka;
	dka.push_back(Node()); dka.push_back(Node());
	dka[1].id = 1; 
	if (nodes[1].is_allowing) { dka[1].is_allowing = true; }
	int cnt = 2;
	queue<set<int>> q;
	q.push(set<int>({ 1 }));
	while (!q.empty())
	{
		auto curr = q.front(); q.pop();
		for (char c = 'a'; c <= 'z'; c++)
		{
			set<int> next;
			bool is_terminating = false;
			for (int elem : curr)
			{
				auto& automata = nodes[elem].edges;
				for (auto nier : automata)
				{
					if (nier.first == c)
					{
						for (auto it = nier.second.begin(); it != nier.second.end(); it++)
						{
							next.insert(*it);
							if (nodes[*it].is_allowing) { is_terminating = true; }
						}
					}
				}
			}
				if (new_q.find(next) == new_q.end())
				{
					q.push(next);
					new_q.insert({ next, cnt });
					dka.push_back(Node()); dka[cnt].id = cnt;
					if (is_terminating) { dka[cnt].is_allowing = true; }
					cnt++;
				}
				dka[new_q.find(curr)->second].edges[c] = new_q.find(next)->second;
		}
	}
	return dka;
}

int main()
{
	freopen("problem5.in", "r", stdin);
	freopen("problem5.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m, k, l;
	cin >> n >> m >> k >> l;
	vector <Non_det_node> nodes(n + 1);
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

	vector <Node> new_nodes = tompson(nodes);
	vector <vector <int>> dp(l + 1, vector <int>(new_nodes.size(), 0));
	dp[0][1] = 1;
	for (int i = 0; i < l; i++)
	{
		for (int j = 1; j < new_nodes.size(); j++)
		{
			auto& automata = new_nodes[j].edges;
			for (auto nier : automata)
			{
				dp[i + 1][nier.second] = (dp[i + 1][nier.second] + dp[i][j]) % MOD;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < new_nodes.size(); i++)
	{
		if (new_nodes[i].is_allowing)
		{
			sum = (sum + dp[l][i]) % MOD;
		}
	}
	cout << sum;

	return 0;
}