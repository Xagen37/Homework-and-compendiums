#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector <long long int> player_father;
vector <long long int> player_exp;

long long int find(long long int x)
{
	if (player_father[x] != x)
	{
		return find(player_father[x]);
	}
	return x;
}

void USSR(long long int x, long long int y)
{
	x = find(x);
	y = find(y);
	if (x == y)
	{
		return;
	}
	player_father[y] = x;
	player_exp[y] -= player_exp[x];
}

long long int count_exp(long long int x)
{
	if (player_father[x] != x)
	{
		return player_exp[x] + count_exp(player_father[x]);
	}
	return player_exp[x];
}

int main()
{
	long long int n, m;
	cin >> n >> m;
	player_father.resize(n);
	player_exp.resize(n);
	for (int i = 0; i < n; i++)
	{
		player_exp[i] = 0;
		player_father[i] = i;
	}

	for (int i = 0; i < m; i++)
	{
		string s;
		cin >> s;
		if (s == "add")
		{
			long long int player, val;
			cin >> player >> val;
			player_exp[find(player - 1)] += val;
		}
		else if (s == "join")
		{
			long long int one, two;
			cin >> one >> two;
			USSR(one - 1, two - 1);
		}
		else
		{
			long long int player;
			cin >> player;
			cout << count_exp(player - 1) << '\n';
		}
	}
	return 0;
}
