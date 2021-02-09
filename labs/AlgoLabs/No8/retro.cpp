#include <iostream>
#include <vector>
#include <queue>

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
				break;
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
				break;
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
	int n, m;
	while (cin >> n)
	{
		cin >> m;
		Graph game(n);

		for (int i = 0; i < m; i++)
		{
			int left, right;
			cin >> left >> right;
			left--; right--;
			game.add_edge(left, right);
		}

		game.calc_pos();
		for (int i = 0; i < n; i++)
		{
			int temp = game.get_pos_type(i);
			if (temp == 1)
			{
				cout << "FIRST\n";
			}
			else if (temp == -1)
			{
				cout << "SECOND\n";
			}
			else
			{
				cout << "DRAW\n";
			}
		}

		cout << '\n';
	}
	return 0;
}