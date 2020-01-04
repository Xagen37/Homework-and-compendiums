#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
vector <string> codes;

void build(string pref, const int& n)
{
	if (pref.size() == n)
	{
		bool flag = true;
		for (int i = 1; i < n; i++)
		{
			if (pref[i] == pref[i - 1] && pref[i] == '1')
			{
				flag = false;
			}
		}
		if (flag)
		{
			codes.push_back(pref);
		}
	}
	else
	{
		build(pref + '0', n);
		build(pref + '1', n);
	}
}

int main()
{
	freopen("vectors.in", "r", stdin);
	freopen("vectors.out", "w", stdout);

	int n;
	cin >> n;
	build("", n);
	cout << codes.size() << '\n';
	for (int i = 0; i < codes.size(); i++)
	{
		cout << codes[i] << '\n';
	}
	return 0;
}
