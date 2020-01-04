#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	freopen("nextchoose.in", "r", stdin);
	freopen("nextchoose.out", "w", stdout);

	int n, k;
	cin >> n >> k;
	vector <int> in(k);
	for (int i = 0; i < k; i++)
	{
		cin >> in[i];
	}

	vector <int> next = in;
	next.push_back(n + 1);
	int i = k - 1;
	while (i >= 0 && next[i + 1] - next[i] < 2)
	{
		i--;
	}
	if (i >= 0)
	{
		next[i]++;
		for (int j = i + 1; j < k; j++)
		{
			next[j] = next[j - 1] + 1;
		}
		for (int j = 0; j < k; j++)
		{
			cout << next[j] << ' ';
		}
	}
	else
	{
		cout << -1;
	}
	return 0;
}
