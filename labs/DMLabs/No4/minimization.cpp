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
#include <list>

using namespace std;
const int MAX_SIZE = 50001;

struct Node
{
	int id = 0;
	int class_id = 0;
	bool is_allowing = false;
	bool is_starting = false;
	bool is_good = false;
	unordered_map<char, int> edges;
};

struct Node_reversed
{
	unordered_map<char, vector <int>> edges;
	int id = 0;
	bool is_allowing = false;
	bool is_starting = false;
};

void dfs(Node * nodes, bool * used, int v)
{
	used[v] = 1;
	for (auto it = nodes[v].edges.begin(); it != nodes[v].edges.end(); it++)
	{
		if (!used[it->second])
		{
			dfs(nodes, used, it->second);
		}
	}
}

void dfs_r(Node_reversed * nodes, bool * used, int v)
{
	used[v] = 1;
	for (auto it = nodes[v].edges.begin(); it != nodes[v].edges.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (!used[it->second[i]])
			{
				dfs_r(nodes, used, it->second[i]);
			}
		}
	}
}

vector <Node>hopcroft_2(Node * nodes, Node_reversed * reversed, int n)
{
	unordered_set<int> terminal, not_terminal;
	for (int i = 1; i < n; i++)
	{
		if (!nodes[i].is_good) { continue; }

		if (nodes[i].is_allowing)
		{
			terminal.insert(i);
			nodes[i].class_id = 1;
		}
		else
		{
			not_terminal.insert(i);
			nodes[i].class_id = 2;
		}
	}
	vector <unordered_set<int> *> P; P.push_back(new unordered_set<int>());
	P.push_back(&terminal); P.push_back(&not_terminal);
	queue<pair<unordered_set<int> *, char>> q;
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		q.emplace(&terminal, ch);
		q.emplace(&not_terminal, ch);
	}

	while (!q.empty())
	{
		pair<unordered_set<int>*, char> c = q.front(); q.pop();
		unordered_map<int, vector<int>> involved;
		for (int elem : *c.first)
		{
			if (reversed[elem].edges.find(c.second) == reversed[elem].edges.end())
			{
				continue;
			}

			for (int cnt = 0; cnt < reversed[elem].edges[c.second].size(); cnt++)
			{
				int i = nodes[reversed[elem].edges[c.second][cnt]].class_id;
				auto nit = involved.find(i);
				if (nit == involved.end())
				{
					involved.insert(nit, { i, vector<int>() });
				}
				involved[i].emplace_back(reversed[elem].edges[c.second][cnt]);
			}
		}
		for (auto it = involved.begin(); it != involved.end(); it++)
		{
			if (it->second.size() < P[it->first]->size())
			{
				int j = P.size();
				P.emplace_back(new unordered_set<int>);
				for (int r = 0; r < it->second.size(); r++)
				{
					P[it->first]->erase(it->second[r]);
					P[j]->emplace(it->second[r]);
				}
				if (P[j]->size() > P[it->first]->size())
				{
					swap(P[it->first], P[j]);
				}
				for (auto pt = P[j]->begin(); pt != P[j]->end(); pt++)
				{
					nodes[*pt].class_id = j;
				}
				for (char ch = 'a'; ch <= 'z'; ch++)
				{
					q.emplace(new unordered_set<int>(*P[j]), ch );
				}
			}
		}
	}

	vector <Node> result; result.push_back(Node());
	int start = -1;
	for (int i = 0; i < P.size(); i++) 
	{
		if (P[i]->empty()) { continue; }
		bool is_start = false;
		for (auto it = P[i]->begin(); it != P[i]->end(); it++)
		{
			if (nodes[*it].is_starting) 
			{ 
				is_start = true; 
				break;
			}
		}
		if (is_start)
		//if (nodes[*P[i].begin()].is_starting)
		{
			start = i;
			Node& representor = nodes[*P[i]->begin()];
			representor.is_starting = true;
			result.push_back(representor);
		}
	}

	for (int i = 0; i < P.size(); i++)
	{
		if (i == start) { continue; }
		if (P[i]->empty()) { continue; }
		Node& representor = nodes[*P[i]->begin()];
		result.push_back(representor);
	}

	for (int i = 1; i < result.size(); i++)
	{
		result[i].id = i;
		auto automata = result[i].edges;
		for (auto it = automata.begin(); it != automata.end(); it++)
		{
			bool is_found = false;
			for (int j = 1; j < result.size(); j++)
			{
				if (result[j].class_id == nodes[it->second].class_id)
				{
					result[i].edges[it->first] = j;
					is_found = true;
					break;
				}
			}
			if (!is_found)
			{
				result[i].edges.erase(it->first);
			}
		}
	}

	return result;
}

int main()
{
	freopen("fastminimization.in", "r", stdin);
	freopen("fastminimization.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;
	Node * nodes = new Node[MAX_SIZE];
	Node_reversed * reversed = new Node_reversed[MAX_SIZE];
	//vector <Node> nodes(n + 1);
	//vector <Node_reversed> reversed(n + 1);
	for (int i = 1; i <= n; i++)
	{
		nodes[i].id = i;
		reversed[i].id = i;
	}
	for (int i = 0; i < k; i++)
	{
		int id;
		cin >> id;
		nodes[id].is_allowing = true;
		reversed[id].is_allowing = true;
	}
	for (int i = 0; i < m; i++)
	{
		int from, to; char c;
		cin >> from >> to >> c;
		nodes[from].edges[c] = to;
		if (reversed[to].edges.find(c) == reversed[to].edges.end())
		{
			reversed[to].edges[c] = vector <int>({ from });
		}
		else
		{
			reversed[to].edges[c].push_back(from);
		}
	}
	nodes[1].is_starting = true;
//-------------------------------------------------
	bool used[MAX_SIZE] = { 0 };
	bool used_reversed[MAX_SIZE] = { 0 };
	//vector <short> used(n + 1, 0);
	//vector <short> used_reversed(n + 1, 0);
	dfs(nodes, used, 1);
	for (int i = 1; i < n + 1; i++)
	{
		if (reversed[i].is_allowing)
		{
			dfs_r(reversed, used_reversed, i);
		}
	}
	for (int i = 1; i < n + 1; i++)
	{
		if (used[i] && used_reversed[i])
		{
			nodes[i].is_good = true;
		}
	}
//------------------------------------------------

	vector <Node> dka = hopcroft_2(nodes, reversed, n + 1);
	//delete[] nodes;
	//delete[] reversed;
	int n1 = dka.size() - 1, m1 = 0, k1 = 0;
	int ks[MAX_SIZE];
	for (int i = 1; i < dka.size(); i++)
	{
		m1 += dka[i].edges.size();
		if (dka[i].is_allowing) { ks[k1] = i; k1++; }
	}
	cout << n1 << ' ' << m1 << ' ' << k1 << '\n';
	if (k1)
	{
		for (int i = 0; i < k1; i++)
		{
			cout << ks[i] << ' ';
		}
		cout << '\n';
	}
	for (int i = 1; i < dka.size(); i++)
	{
		for (const pair <char, int>& nier : dka[i].edges)
		{
			cout << i << ' ' << nier.second << ' ' << nier.first << '\n';
		}
	}

	return 0;
}
