#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, x, y, a0;
	cin >> n >> x >> y >> a0;
	unsigned long long pref[10000002] = {0};
	pref[0] = 0;
	pref[1] = a0;
	for (int i = 2; i <= n; i++)
	{
		a0 = (x * a0 + y) % 65536;
		pref[i] = pref[i - 1] + a0;
	}

	int m, z, t, b0;
	cin >> m >> z >> t >> b0;
	if (!m) { cout << 0; return 0; }
	
	unsigned c0 = b0 % n;
	unsigned c1 = 0;
	unsigned long long  sum = 0;
	for (int i = 1; i < 2 * m; i++)
	{
		b0 = ((z * b0 + t) % 1073741824 + 1073741824) % 1073741824;
		c1 = c0;
		c0 = b0 % n;

		if (i % 2)
		{
			int  l = min(c0, c1);
			int  r = max(c0, c1);
			sum += pref[r + 1] - pref[l];
		}
	}

	cout << sum;
	return 0;
}
