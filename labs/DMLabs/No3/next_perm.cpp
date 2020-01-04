#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	freopen("nextperm.in", "r", stdin);
	freopen("nextperm.out", "w", stdout);
	int n;
	cin >> n;
	vector <int> in(n);
	for (int i = 0; i < n; i++)
	{
		cin >> in[i];
	}
	vector <int> prev = in;
	vector <int> next = in;

	bool flag = false;
	for (int i = n - 2; i >= 0; i--)
	{
		if (next[i] < next[i + 1])
		{
			flag = true;
			int m_id = i + 1;
			for (int k = i + 1; k < n; k++)
			{
				if (next[k] < next[m_id] && next[k] > next[i])
				{
					m_id = k;
				}
			}
			swap(next[i], next[m_id]);
			reverse(next.begin() + i + 1, next.end());
			break;
		}
	}
	if (!flag)
	{
		next = vector <int>(n, 0);
	}

	flag = false;
	for (int i = n - 2; i >= 0; i--)
	{
		if (prev[i] > prev[i + 1])
		{
			flag = true;
			int m_id = i + 1;
			for (int k = i + 1; k < n; k++)
			{
				if (prev[k] > prev[m_id] && prev[k] < prev[i])
				{
					m_id = k;
				}
			}
			swap(prev[i], prev[m_id]);
			reverse(prev.begin() + i + 1, prev.end());
			break;
		}
	}
	if (!flag)
	{
		prev = vector <int>(n, 0);
	}
	for (int i = 0; i < n; i++)
	{
		cout << prev[i] << ' ';
	}
	cout << '\n';
	for (int i = 0; i < n; i++)
	{
		cout << next[i] << ' ';
	}
	return 0;
}