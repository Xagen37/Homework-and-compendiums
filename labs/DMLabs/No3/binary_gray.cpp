#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void build(vector <string> pref, const int& n)
{
	if (pref[0].size() == n)
	{
		for (int i = 0; i < pref.size(); i++)
		{
			cout << pref[i] << '\n';
		}
	}
	else
	{
		vector <string> g;
		for (int i = 0; i < pref.size(); i++)
		{
			g.push_back('0' + pref[i]);
		}
		for (int i = pref.size() - 1; i >= 0; i--)
		{
			g.push_back('1' + pref[i]);
		}
		build(g, n);
	}
}

int main()
{
	freopen("gray.in", "r", stdin);
	freopen("gray.out", "w", stdout);

	int n;
	cin >> n;
	vector <string> start(1, "");
	build(start, n);
	return 0;
}
