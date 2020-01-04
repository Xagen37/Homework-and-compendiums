#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int n, k;

void build(int prev, vector <int> ch)
{
	if (ch.size() == k)
	{
		for (int i = 0; i < ch.size(); i++)
		{
			cout << ch[i] << ' ';
		}
		cout << '\n';
		return;
	}

	for (int i = prev + 1; i <= n; i++)
	{
		ch.push_back(i);
		build(i, ch);
		ch.pop_back();
	}
}

int main()
{
	freopen("choose.in", "r", stdin);
	freopen("choose.out", "w", stdout);
	
	cin >> n >> k;
	build(0, vector <int>());
	return 0;
}
