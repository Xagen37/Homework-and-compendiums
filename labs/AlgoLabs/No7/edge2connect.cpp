#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <stack>

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
	using bridge_map_t = unordered_map <pair <int, int>, vector <int>, Hasher>;
	using stack_t = stack <int>;

	Graph(int n)
		: gr(n),
		used(n, 0),
		in(n),
		up(n),
		top_sort(n),
		comps(n)
	{}

	void add_edge(int from, int to)
	{
		gr[from].push_back(to);
	}

	set<int>& find_bridges(bridge_map_t& e_map)
	{
		int timer = 0;
		stack_t st;
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				bridge_dfs(i, -1, timer, e_map, st);
				while (!st.empty())
				{
					comps[st.top()] = comp_cnt;
					st.pop();
				}
				comp_cnt++;
			}
		}
		comp_cnt--;

		return bridges;
	}

	vector <int>& get_comps() 
	{
		return comps;
	}

	int get_comp_cnt()
	{
		return comp_cnt;
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
	void bridge_dfs(int v, int p, int& timer, bridge_map_t& e_map, stack_t& st)
	{
		st.push(v);
		in[v] = up[v] = timer++;
		used[v] = 1;

		for (auto u : gr[v])
		{
			if (u == p) { continue; }
			if (!used[u])
			{
				bridge_dfs(u, v, timer, e_map, st);
				up[v] = min(up[v], up[u]);
			}
			else
			{
				up[v] = min(up[v], in[u]);
			}
		}
		if (up[v] == in[v] && p != -1 && e_map[{p, v}].size() == 1)
		{
			bridges.insert(e_map[{p, v}].front());
			int pop;
			do
			{
				pop = st.top();
				st.pop();
				comps[pop] = comp_cnt;
			} while (!st.empty() && pop != v);
			comp_cnt++;
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
	vector <int> comps;
	int comp_cnt = 1;
	set <int> bridges;
	set <int> cutpoints;
	//vector <vector <int>> comps;

	bool cycle = false;
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	unordered_map <pair <int, int>, vector <int>, Graph::Hasher> e_map;


	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		s--; f--;

		graph.add_edge(s, f);
		graph.add_edge(f, s);
		e_map[{s, f}].push_back(i + 1);
		e_map[{f, s}].push_back(i + 1);
	}

	graph.find_bridges(e_map);

	vector <int>& cs = graph.get_comps();
	cout << graph.get_comp_cnt() << '\n';

	for (size_t i = 0; i < cs.size(); i++)
	{
		cout << cs[i] << ' ';
	}

	return 0;
}