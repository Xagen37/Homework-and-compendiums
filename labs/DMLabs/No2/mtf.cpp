#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	freopen("mtf.in", "r", stdin);
	freopen("mtf.out", "w", stdout);

	map <char, int> list;
	for (char i = 'a'; i < 'z' + 1; i++)
	{
		list[i] = i - 'a' + 1;
	}
	string s;
	cin >> s;

	for (int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		cout << list[c] << ' ';

		if (list[c] != 1)
		{
			for (char k = 'a'; k < 'z' + 1; k++)
			{
				if (list[k] < list[c])
				{
					list[k] ++;
				}
			}
			list[c] = 1;
		}
	}

	return 0;
}