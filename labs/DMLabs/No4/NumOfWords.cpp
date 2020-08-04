#include <algorithm>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iostream>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;
bool is_cycle = false;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	bool good = false;
	unordered_map<char, int> edges;
};
struct Node_reversed
{
	int id = 0;
	bool is_allowing = false;
	vector <int> edges;
};

void dfs(vector<Node>& nodes, vector <int>& used, int v)
{
	used[v] = 1;
	auto & automata = nodes[v].edges;
	for (auto it = automata.begin(); it != automata.end(); it++)
	{
		if (!used[it->second])
		{
			dfs(nodes, used, it->second);
		}
	}
}

void dfs(vector<Node_reversed>& nodes, vector <int>& used, int v)
{
	used[v] = 1;
	auto & automata = nodes[v].edges;
	for (auto it = automata.begin(); it != automata.end(); it++)
	{
		if (!used[*it])
		{
			dfs(nodes, used, *it);
		}
	}
}

void dfs_cycle(vector <Node> & nodes, vector <int>& used, int v)
{
	used[v] = 1;
	if (!nodes[v].good)
	{
		used[v] = 2;
		return;
	}
	auto & automata = nodes[v].edges;
	for (auto it = automata.begin(); it != automata.end(); it++)
	{
		if (used[it->second] == 1)
		{
			is_cycle = true;
			return;
		}
		else if (!used[it->second])
		{
			dfs_cycle(nodes, used, it->second);
			if (is_cycle) { return; }
		}
	}
	used[v] = 2;
}

int cnt = 0;

vector <int> dp;
vector <int> top;

void top_dfs(vector <Node>& nodes, vector <int>& used, int v)
{
	used[v] = 1;
	if (!nodes[v].good) { return; }
	auto& automata = nodes[v].edges;
	for (auto nier : automata)
	{
		if (!used[nier.second])
		{
			top_dfs(nodes, used, nier.second);
		}
	}
	top.push_back(v);
}

void top_sort(vector <Node>& nodes)
{
	vector <int> used(nodes.size(), 0);
	for (int i = 1; i < nodes.size(); i++)
	{
		if (!used[i] && nodes[i].good)
		{
			top_dfs(nodes, used, i);
		}
	}
	reverse(top.begin(), top.end());
}


void top_count(vector <Node>& nodes)
{
	if (dp.size() <= 1 || nodes.size() <= 1) { return; }
	dp[1] = 1;
	for (int i = 0; i < top.size(); i++)
	{
		if (!nodes[top[i]].good) { continue; }
		auto& automata = nodes[top[i]].edges;
		for (auto nier : automata)
		{
			dp[nodes[nier.second].id] = (dp[nodes[nier.second].id] + dp[nodes[top[i]].id]) % MOD;
		}
	}
}

void print(ostream& out, vector <Node>& nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		out << nodes[i].id << " - " << nodes[i].is_allowing << '\n';
		for (auto it = nodes[i].edges.begin(); it != nodes[i].edges.end(); it++)
		{
			out << '\t' << it->first << " -> " << it->second << '\n';
		}
	}
}

int main()
{
	freopen("problem3.in", "r", stdin);
	freopen("problem3.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//ifstream in("a.txt");
	//ofstream log("log.txt");

	int n, m, k; 
	cin >> n >> m >> k;
	vector <Node> nodes(n + 1);
	vector <Node_reversed> reversed(n + 1);
	for (int i = 1; i <= n; i++)
	{
		nodes[i].id = i;
		reversed[i].id = i;
	}
	for (int i = 0; i < k; i++)
	{
		int num; 
		cin >> num;
		nodes[num].is_allowing = true;
		reversed[num].is_allowing = true;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b; char c;
		cin >> a >> b >> c;
		nodes[a].edges[c] = b;
		reversed[b].edges.push_back(a);
	}

	vector <int> used_start(n + 1, 0);
	dfs(nodes, used_start, 1);
	vector <int> used_terminal_all(n + 1, 0);
	int cnt_k = 0;
	for (int i = 1; i <= n; i++)
	{
		//vector <int> used_terminal(n + 1, 0);
		if (reversed[i].is_allowing)
		{
			dfs(reversed, used_terminal_all, i);
			cnt_k++;
		}
		if (cnt_k >= k) { break; }
	}
	/*reversed.clear();
	reversed.shrink_to_fit();*/

	for (int i = 1; i <= n; i++)
	{
		if (used_start[i] && used_terminal_all[i])
		{
			nodes[i].good = true;
		}
	}

	/*for (int i = 1; i < intersection.size(); i++)
	{
		auto & automata = intersection[i]->edges;
		for (auto nier : automata)
		{
			//int prev = nier.second;
			bool found = false;
			for (int j = 1; j < intersection.size(); j++)
			{
				if (intersection[j]->id == nier.second)
				{
					intersection[i]->edges[nier.first] = j;
					found = true;
					break;
				}
			}
			if (!found) { intersection[i]->edges.erase(nier.first); }
		}
	}*/


	used_start.assign(n + 1, 0);
	dfs_cycle(nodes, used_start, 1);
	if (is_cycle) { cout << -1; return 0; }

	dp.resize(n + 1, 0);
	top_sort(nodes);
	top_count(nodes);
	int sum = 0;
	for (int i = 0; i < dp.size(); i++)
	{
		if (nodes[i].is_allowing)
		{
			sum = (sum + dp[i]) % MOD;
		}
	}
	cout << sum;
	
	return 0;
}