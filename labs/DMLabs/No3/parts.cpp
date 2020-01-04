#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int n;

void build(int prev, vector <int> part, int sum)
{
	if (sum >= n)
	{
		if (sum == n)
		{
			cout << part[0];
			for (int i = 1; i < part.size(); i++)
			{
				cout << '+' << part[i];
			}
			cout << '\n';
		}
		return;
	}

	for (int i = prev; i <= n; i++)
	{
		if (sum + i <= n)
		{
			part.push_back(i);
			build(i, part, sum + i);
			part.pop_back();
		}
		else
		{
			break;
		}
	}
}

int main()
{
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);

	cin >> n;
	build(1, vector <int>(), 0);

	return 0;
}
