#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <set>
#include <utility>

using namespace std;

struct Graph
{
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
	using bridge_map_t = unordered_map <pair <int, int>, int, Hasher>;
	using stack_t = stack <pair <int, int>>;

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
		stack_t st;
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				//max_colour++;
				point_dfs(i, -1, timer, st);
			}
		}

		return cutpoints;
	}

	bridge_map_t& get_colours()
	{
		return colours;
	}

	int get_colour_cnt()
	{
		return max_colour - 1;
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

	void point_dfs(int v, int p, int& timer, stack_t& st)
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
				st.push({ v, u });
				point_dfs(u, v, timer, st);

				if (up[u] >= in[v])
				{
					int colour = max_colour++;
					while (st.top() != make_pair(v, u))
					{
						int f = st.top().first;
						int s = st.top().second;
						colours[{f, s}] = colour;
						colours[{s, f}] = colour;
						st.pop();
					}
					colours[{v, u}] = colour;
					colours[{u, v}] = colour;
					st.pop();
					cutpoints.insert(v);
				}
				up[v] = min(up[v], up[u]);
			}
			else if (in[u] < in[v])
			{
				st.push({ v, u });
				up[v] = min(up[v], in[u]);
			}
			else if (in[u] < up[v])
			{
				up[v] = up[u];
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
	bridge_map_t colours;
	int max_colour = 1;

	bool cycle = false;
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	vector <pair <int, int>> es(m);

	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		s--; f--;
		es[i] = {s, f};
		graph.add_edge(s, f);
		graph.add_edge(f, s);
	}

	graph.find_cutpoints();
	auto& cs = graph.get_colours();
	cout << graph.get_colour_cnt() << '\n';

	for (int i = 0; i < m; i++)
	{
		cout << cs[es[i]] << ' ';
	}

	return 0;
}