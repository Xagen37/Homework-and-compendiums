#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void build(vector <bool> & used, const int & n, vector <int> & perm)
{
	if (perm.size() == n)
	{
		for (int i = 0; i < perm.size(); i++)
		{
			cout << perm[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = 0; i < used.size(); i++)
	{
		if (!used[i])
		{
			perm.push_back(i + 1);
			used[i] = true;
			build(used, n, perm);
			used[i] = false;
			perm.pop_back();
		}
	}
}

int main()
{
	freopen("permutations.in", "r", stdin);
	freopen("permutations.out", "w", stdout);

	int n;
	cin >> n;
	vector <bool> used(n, false);
	vector <int> perm;
	build(used, n, perm);

	return 0;
}