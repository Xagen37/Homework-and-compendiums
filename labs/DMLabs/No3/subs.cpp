#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

int main()
{
	freopen("subsets.in", "r", stdin);
	freopen("subsets.out", "w", stdout);

	int n;
	cin >> n;
	vector <int> start(n);
	for (int i = 0; i < n; i++)
	{
		start[i] = i + 1;
	}
	set <vector <int>> answ;
	for (int i = 0; i < (1 << n); i++)
	{
		vector <int> curr;
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j))
			{
				curr.push_back(start[j]);
			}
		}
		answ.insert(curr);
	}

	for (vector <int> v : answ)
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << ' ';
		}
		cout << '\n';
	}
	return 0;
}