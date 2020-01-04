#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main()
{
	freopen("nextvector.in", "r", stdin);
	freopen("nextvector.out", "w", stdout);

	string in;
	cin >> in;
	string prev, next;
	prev = next = in;
	int i = next.length() - 1;
	bool changed = false;
	while (i >= 0)
	{
		if (next[i] == '0')
		{
			changed = true;
			next[i] = '1';
			for (int k = i + 1; k < next.size(); k++)
			{
				next[k] = '0';
			}
			break;
		}
		else
		{
			i--;
		}
	}
	if (!changed)
	{
		next = "-";
	}

	i = prev.size() - 1;
	changed = false;
	while (i >= 0)
	{
		if (prev[i] == '1')
		{
			changed = true;
			prev[i] = '0';
			for (int k = i + 1; k < prev.size(); k++)
			{
				prev[k] = '1';
			}
			break;
		}
		else
		{
			i--;
		}
	}
	if (!changed)
	{
		prev = "-";
	}

	cout << prev << '\n' << next;
	return 0;
}