#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
	Graph(int n)
		: gr(n),
		  used(n, 0),
		  top_sort(n)
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
		int cnt = used.size() - 1;
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				top_sort_dfs(i, cnt);
			}
		}
		return top_sort;
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

	void top_sort_dfs(int v, int& cnt)
	{
		used[v] = 2;
		for (auto u : gr[v])
		{
			if (!used[u])
			{
				top_sort_dfs(u, cnt);
			}
		}
		top_sort[cnt--] = v;
	}

	vector <vector <int>> gr;
	vector <int> used;
	vector <int> top_sort;
	bool cycle = false;
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
		s--;
		f--;
		graph.add_edge(s, f);
	}

	graph.dfs();
	if (!graph.is_cycle())
	{
		const vector<int>& ts = graph.make_top_sort();
		for (size_t i = 0; i < ts.size(); i++)
		{
			cout << ts[i] + 1 << ' ';
		}
	}
	else
	{
		cout << -1;
	}

	return 0;
}