#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;
vector <string> triple;

void build_triple(string pref, const int & n)
{
	if (pref.size() == n) 
	{
		triple.push_back(pref);
	}
	else
	{
		build_triple(pref + '0', n);
		build_triple(pref + '1', n);
		build_triple(pref + '2', n);
	}
}

void build_anti()
{
	for (int i = 0; i < triple.size() / 3; i++)
	{
		for (int k = 0; k < 3; k++) 
		{
			cout << triple[i] << '\n';
			for (int j = 0; j < triple[i].size(); j++)
			{
				triple[i][j] = '0' + (triple[i][j] + 1) % 3;
			}
		}
	}
}
int main()
{
	freopen("antigray.in", "r", stdin);
	freopen("antigray.out", "w", stdout);

	int n;
	cin >> n;
	build_triple("", n);
	build_anti();

	return 0;
}