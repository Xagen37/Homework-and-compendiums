#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	freopen("nextbrackets.in", "r", stdin);
	freopen("nextbrackets.out", "w", stdout);
	string in;
	cin >> in;
	int cnt_close = 0;
	int cnt_open = 0;

	for (int i = in.length() - 1; i >= 0; i--)
	{
		if (in[i] == '(')
		{
			cnt_open++;
			if (cnt_close > cnt_open)
			{
				break;
			}
		}
		else
		{
			cnt_close++;
		}
	}
	string next = in.substr(0, in.length() - cnt_open - cnt_close);
	if (next == "")
	{
		cout << "-";
		return 0;
	}
	next += ')';
	for (int i = 0; i < cnt_open; i++)
	{
		next += '(';
	}
	for (int i = 1; i < cnt_close; i++)
	{
		next += ')';
	}
	cout << next;
	return 0;
}
