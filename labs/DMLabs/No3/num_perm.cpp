#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
long long int n, k;
const long long int fact[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000};
void build(vector <long long int>& pref, vector <bool> used)
{
	if (pref.size() == n)
	{
		return;
	}
	for (int i = 0; i < used.size(); i++)
	{
		if (used[i])
		{
			continue;
		}
		if (fact[n - pref.size() - 1] > k)
		{
			pref.push_back(i + 1);
			used[i] = 1;
			build(pref, used);
			return;
		}
		else
		{
			k -= fact[n - pref.size() - 1];
		}
	}
}

int main()
{
	//freopen("num2perm.in", "r", stdin);
	//freopen("num2perm.out", "w", stdout);

	cin >> n >> k;
	vector <long long int> answ;
	vector <bool> used(n, false);
	build(answ, used);
	for (int i = 0; i < n; i++)
	{
		cout << answ[i] << ' ';
	}

	return 0;
}