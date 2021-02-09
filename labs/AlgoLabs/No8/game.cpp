#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

struct Graph
{
	Graph(size_t n)
		: gr(n)
		, r_gr(n)
		, pos_type(n, 0)
		, next_win_count(n, 0)
	{}

	void add_edge(size_t from, size_t to)
	{
		gr[from].push_back(to);
		r_gr[to].push_back(from);
	}

	void calc_pos()
	{
		queue <int> q;
		for (int i = 0; i < pos_type.size(); i++)
		{
			if (gr[i].empty())
			{
				q.push(i);
				pos_type[i] = -1;
			}
		}

		while (!q.empty())
		{
			int curr = q.front(); q.pop();
			switch (pos_type[curr])
			{
				case 1: 
				{
					for (auto it : r_gr[curr])
					{
						if (!pos_type[it])
						{
							if (++next_win_count[it] == gr[it].size())
							{
								pos_type[it] = -1;
								q.push(it);
							}
						}
					}
				}
				case -1:
				{
					for (auto it : r_gr[curr])
					{
						if (!pos_type[it])
						{
							pos_type[it] = 1;
							q.push(it); 
						}
					}
				}
			}
		}
	}

	int get_pos_type(size_t pos)
	{
		return pos_type[pos];
	}

private:
	vector <vector <int>> gr;
	vector <vector <int>> r_gr;
	vector <int> pos_type; //-1 <=> lose; 0 <=> draw; 1 <=> win
	vector <int> next_win_count;
};

int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);

	int n, m, s;
	cin >> n >> m >> s; s--;
	Graph game(n);

	for (int i = 0; i < m; i++)
	{
		int left, right;
		cin >> left >> right;
		left--; right--;
		game.add_edge(left, right);
	}

	game.calc_pos();
	int temp = game.get_pos_type(s);
	if (temp == 1)
	{
		cout << "First player wins";
	}
	else if (temp == -1)
	{
		cout << "Second player wins";
	}
	else
	{
		throw temp;
	}

	return 0;
}