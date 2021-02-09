#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <set>

using namespace std;

struct Graph_grundy
{
	Graph_grundy(size_t n)
		: gr(n)
		, r_gr(n)
		, pos_type(n, 0)
		, mex_max(n, {0, -1})
	{}

	void add_edge(size_t from, size_t to)
	{
		gr[from].insert(to);
		r_gr[to].insert(from);
	}

	int get_pos_type(size_t pos)
	{
		return pos_type[pos];
	}

	void calc_grundy()
	{
		top_sort_and_calc_pos();
	}

private:
	vector <set <int>> gr;
	vector <set <int>> r_gr;
	vector <int> pos_type; // Grundy function
	vector <pair <int, int>> mex_max;

	void top_sort_and_calc_pos()
	{
		vector <int> used(gr.size(), 0);
		vector <int> res;
		function<void(int)> dfs = [&](int v)
		{
			used[v] = 1;
			for (auto u : gr[v])
			{
				if (!used[u])
				{
					dfs(u);
				}
			}
			res.push_back(v);
		};
		for (int i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				dfs(i);
			}
		}

		for (int i = 0; i < res.size(); i++)
		{
			int curr = res[i];
			int cnt = 0;
			set <int> grundy_values;
			for (auto it : gr[curr])
			{
				grundy_values.insert(pos_type[it]);
			}
			
      int mex;
			for (int k = 0; ; k++)
			{
        if (!grundy_values.count(k))
        {
          mex = k;
          break;
        }
			}

			pos_type[curr] = mex;
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	Graph_grundy game(n);

	for (int i = 0; i < m; i++)
	{
		int left, right;
		cin >> left >> right;
		left--; right--;
		game.add_edge(left, right);
	}

	game.calc_grundy();

	for (int i = 0; i < n; i++)
	{
		cout << game.get_pos_type(i) << '\n';
	}

	return 0;
}