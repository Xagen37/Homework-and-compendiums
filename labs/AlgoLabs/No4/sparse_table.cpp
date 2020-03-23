#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	long long int pows[21];
	pows[0] = 1;
	for (int i = 1; i < 21; i++)
	{
		pows[i] = (pows[i - 1] << 1);
	}

	long long int n, m, a1;
	cin >> n >> m >> a1;
	long long int u, v;
	cin >> u >> v;
	
	vector <long long int> a(n);
	a[0] = a1;
	for (long long int i = 1; i < n; i++)
	{
		a[i] = (a[i - 1] * 23 + 21563) % 16714589;
	}

	long long int pow = lower_bound(pows, pows + 21, n) - pows;
	vector <vector <long long int>> mi(100000, vector <long long int>(17));
	for (long long int i = 0; i < n; i++)
	{
		mi[i][0] = a[i];
	}

	for (long long int k = 1; (1LL << k) <= n; k++)
	{
		for (long long int i = 0; (i + (1LL << k) - 1) < n; i++)
		{
			mi[i][k] = min(mi[i][k - 1], mi[i + (1LL << (k - 1))][k - 1]);
		}
	}

	long long int r = 0;
	for (long long int i = 1; i <= m; i++)
	{
		long long int ue = u;
		long long int ve = v;
		ue--;
		ve--;
		if (ue > ve) { swap(ue, ve); }
		ve++;
		long long int d = ve - ue;
		long long int k = (long long int)log2(ve - ue);
		r = min(mi[ue][k], mi[ve - (1LL << k)][k]);
		if (i == m) { break; }
		u = ((17 * u + 751 + r + 2LL * i) % n) + 1;
		v = ((13 * v + 593 + r + 5LL * i) % n) + 1;
	}
	cout << u << ' ' << v << ' ' << r << '\n';
	return 0;
}