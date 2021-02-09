#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Graph
{
	using matrix_t = vector <vector <int>>;
	Graph(int n, matrix_t && m)
		: matrix(std::forward<matrix_t>(m)),
		  used(n, 0)
	{
		trans.resize(n, vector <int>(n));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				trans[j][i] = matrix[i][j];
			}
		}
	}

	int operator() ()
	{
		int left = -1, right = 1e9 + 1;
		while (right - left > 1)
		{
			int m = left + (right - left) / 2;
			if (check_dfs(m))
			{
				right = m;
			}
			else
			{
				left = m;
			}
		}
		return check_dfs(right) ? right : left;
	}

private:

	void top_sort_dfs(int v, int vol)
	{
		used[v] = 2;
		for (size_t u = 0; u < used.size(); u++)
		{
			if (!used[u] && matrix[v][u] <= vol)
			{
				top_sort_dfs(u, vol);
			}
		}
		top_sort.push_back(v);
	}

	void make_top_sort(int vol)
	{
		used.assign(used.size(), 0);
		for (size_t i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				top_sort_dfs(i, vol);
			}
		}
		reverse(top_sort.begin(), top_sort.end());
	}

	void mark_dfs(int v, int col, int vol)
	{
		used[v] = col;
		for (size_t u = 0; u < used.size(); u++)
		{
			if (u == v) { continue; }
			if (!used[u] && trans[v][u] <= vol)
			{
				mark_dfs(u, col, vol);
			}
		}
	}

	bool mark_and_check(int vol)
	{
		int col = 1;
		used.assign(used.size(), 0);
		for (int i = 0; i < used.size(); i++)
		{
			if (!used[top_sort[i]])
			{
				mark_dfs(top_sort[i], col, vol);
				col++;
			}
		}

		return col == 2;
	}

	bool check_dfs(int vol)
	{
		make_top_sort(vol);
		return mark_and_check(vol);
	}

	matrix_t matrix, trans;
	vector <int> used;
	vector <int> top_sort;
};



int main()
{
	ifstream in("avia.in");
	ofstream out("avia.out");

	int n;
	in >> n;
	Graph::matrix_t mat(n, vector <int>(n));
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in >> mat[i][j];
		}
	}
	
	Graph graph(n, std::move(mat));

	out << graph();

	return 0;
}