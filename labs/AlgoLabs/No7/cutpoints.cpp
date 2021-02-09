#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

struct Graph
{
	struct Hasher;
	using bridge_map_t = unordered_map <pair <int, int>, int, Hasher>;

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

	set<int>& find_bridges(bridge_map_t& e_map)
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

	set<int>& find_cutpoints()
	{
		int timer = 0;
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				point_dfs(i, -1, timer);
			}
		}

		return cutpoints;
	}

	bool is_cycle() { return cycle; }

private:
	void bridge_dfs(int v, int p, int& timer, bridge_map_t& e_map)
	{
		in[v] = up[v] = timer++;
		used[v] = 1;

		for (auto u : gr[v])
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

	void point_dfs(int v, int p, int& timer)
	{
		up[v] = in[v] = timer++;
		used[v] = 1;
		int cnt = 0;
		for (auto u : gr[v])
		{
			if (u == p) { continue; }
			if (!used[u])
			{
				cnt++;
				point_dfs(u, v, timer);

				up[v] = min(up[v], up[u]);
				if (p != -1 && up[u] >= in[v])
				{
					cutpoints.insert(v);
				}
			}
			else
			{
				up[v] = min(up[v], in[u]);
			}
		}

		if (p == -1 && cnt > 1)
		{
			cutpoints.insert(v);
		}
	}

	vector <vector <int>> gr;
	vector <int> used;
	vector <int> in;
	vector <int> up;
	vector <int> top_sort;
	set <int> bridges;
	set <int> cutpoints;

	bool cycle = false;

public:
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
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph(n);

	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		s--; f--;
		graph.add_edge(s, f);
		graph.add_edge(f, s);
	}

	set <int> cp = graph.find_cutpoints();

	cout << cp.size() << '\n';
	for (auto p : cp)
	{
		cout << p + 1 << ' ';
	}

	return 0;
}