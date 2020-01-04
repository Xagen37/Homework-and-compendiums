#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	freopen("nextmultiperm.in", "r", stdin);
	freopen("nextmultiperm.out", "w", stdout);

	int n;
	cin >> n;
	vector <int> in(n);
	for (int i = 0; i < n; i++)
	{
		cin >> in[i];
	}
	int i = n - 2;
	while (i >= 0 && in[i] >= in[i + 1])
	{
		i--;
	}
	if (i >= 0)
	{
		int j = i + 1;
		while (j < n - 1 && in[j + 1] > in[i])
		{
			j++;
		}
		swap(in[i], in[j]);
		reverse(in.begin() + i + 1, in.end());
		for (int i = 0; i < in.size(); i++)
		{
			cout << in[i] << ' ';
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			cout << 0 << ' ';
		}
	}
	return 0;
}
