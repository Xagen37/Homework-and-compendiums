#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int n;
void build(string pref, int balance)
{
	if (pref.length() == 2 * n)
	{
		if (!balance)
		{
			cout << pref << '\n';
		}
		return;
	}

	build(pref + '(', balance + 1);
	if (balance > 0)
	{
		build(pref + ')', balance - 1);
	}
}
int main()
{
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);

	cin >> n;
	build("", 0);

	return 0;
}