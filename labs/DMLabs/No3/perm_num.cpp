#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int n;
long long int cnt = 0;

const long long int fact[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000 };

void build(vector <int> perm, vector <bool> used)
{
	if (perm.empty())
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			if (perm[0] == i + 1)
			{
				used[i] = 1;
				build(vector <int>(perm.begin() + 1, perm.end()), used);
				return;
			}
			else
			{
				cnt += fact[perm.size() - 1];
			}
		}
	}
}
int main()
{
	freopen("perm2num.in", "r", stdin);
	freopen("perm2num.out", "w", stdout);
	
	cin >> n;
	vector <int> start(n);
	for (int i = 0; i < n; i++)
	{
		cin >> start[i];
	}
	vector <bool> used(n, false);
	build(start, used);
	cout << cnt;

	return 0;
}