#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void build(string pref, const int & n)
{
	if (pref.size() == n)
	{
		cout << pref << '\n';
	}
	else
	{
		build(pref + '0', n);
		build(pref + '1', n);
	}
}

int main()
{
	freopen("allvectors.in", "r", stdin);
	freopen("allvectors.out", "w", stdout);

	int n;
	cin >> n;
	build("", n);
	return 0;
}
