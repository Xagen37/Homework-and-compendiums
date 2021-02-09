#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

struct Hasher
{
	using key_t = pair<int, int>;
	const int MULT = 239;
	const int MOD = 1e9 + 7;

	std::size_t operator()(const key_t& key) const
	{
		return (((key.first * MULT) % MOD) + key.second) % MOD;
	}
};

struct Graph
{
	using map_t = unordered_map <pair <int, int>, int, Hasher>;

	Graph(int n)
		: gr(n),
		used(n, 0),
		in(n),
		up(n),
		top_sort(n)
	{}

	void add_edge(int from, int to)
	{
		gr[from].push_back(to);
	}

	set<int>& find_bridges(map_t& e_map)
	{
		int timer = 0;
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				bridge_dfs(i, -1, timer, e_map);
			}
		}

		return bridges;
	}

	bool is_cycle() { return cycle; }

private:
	void bridge_dfs(int v, int p, int& timer, map_t& e_map)
	{
		in[v] = up[v] = timer++;
		used[v] = 1;

		for (auto u: gr[v])
		{
			if (u == p) { continue; }
			if (!used[u])
			{
				bridge_dfs(u, v, timer, e_map);
				up[v] = min(up[v], up[u]);
			}
			else
			{
				up[v] = min(up[v], in[u]);
			}
		}
		if (up[v] == in[v] && p != -1)
		{
			bridges.insert(e_map[{p, v}]);
		}
	}

	vector <vector <int>> gr;
	vector <int> used;
	vector <int> in;
	vector <int> up;
	vector <int> top_sort;
	set <int> bridges;

	bool cycle = false;
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	unordered_map <pair <int, int>, int, Hasher> e_map;

	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		s--; f--;
		graph.add_edge(s, f);
		graph.add_edge(f, s);
		e_map[{s, f}] = i + 1;
		e_map[{f, s}] = i + 1;
	}

	set<int>& brs = graph.find_bridges(e_map);
	cout << brs.size() << '\n';
	for (auto e : brs)
	{
		cout << e << ' ';
	}

	return 0;
}