#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Graph
{
	Graph(int n)
		: gr(n),
		used(n, 0),
		top_sort(0),
		marks(n, 0)
	{}

	void add_edge(int from, int to)
	{
		gr[from].push_back(to);
	}

	void dfs()
	{
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				dfs(i);
			}
		}
	}

	vector <int>& make_top_sort()
	{
		used.assign(used.size(), 0);
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				top_sort_dfs(i);
			}
		}
		reverse(top_sort.begin(), top_sort.end());
		return top_sort;
	}

	void mark(vector <int>& tp)
	{
		int cnt = 1;
		for (int i = 0; i < tp.size(); i++)
		{
			if (!marks[tp[i]])
			{
				mark_dfs(tp[i], cnt);
				cnt++;
			}
		}
	}

	int get_edge_num()
	{
		return mark_cnt;
	}

	bool is_cycle() { return cycle; }

private:
	void dfs(int v)
	{
		used[v] = 1;
		for (auto u : gr[v])
		{
			if (!used[u])
			{
				dfs(u);
			}
			else if (used[u] == 1)
			{
				cycle = true;
			}
			if (cycle) { return; }
		}
		used[v] = 2;
	}

	void top_sort_dfs(int v)
	{
		used[v] = 2;
		for (auto u : gr[v])
		{
			if (!used[u])
			{
				top_sort_dfs(u);
			}
		}
		top_sort.push_back(v);
	}

	void mark_dfs(int v, int cnt)
	{
		marks[v] = cnt;
		for (auto u : gr[v])
		{
			if (!marks[u])
			{
				mark_dfs(u, cnt);
			}
			else if (marks[u] != cnt)
			{
				if (edges.count({ cnt, marks[u] }) == 0)
				{
					mark_cnt++;
					edges.insert({ cnt, marks[u] });
				}
			}
		}
	}

	vector <vector <int>> gr;
	vector <int> used;
	vector <int> top_sort;
	vector <int> marks;
	set <pair <int, int>> edges;
	int mark_cnt = 0;
	bool cycle = false;
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph(n), reversed(n);

	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		s--; f--;
		graph.add_edge(s, f);
		reversed.add_edge(f, s);
	}

	auto& tp = graph.make_top_sort();
	reversed.mark(tp);
	cout << reversed.get_edge_num();

	return 0;
}