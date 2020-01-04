#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

void build(vector<string> & pref, const int& n, const int& k)
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
		vector <string> next;
		for (int i = 0; i < k; i++)
		{
			if (i % 2)
			{
				for (int j = 0; j < pref.size(); j++)
				{
					next.push_back((char)(i + '0') + pref[j]);
				}
			}
			else
			{
				for (int j = pref.size() - 1; j >= 0; j--)
				{
					next.push_back((char)(i + '0') + pref[j]);
				}
			}
		}
		build(next, n, k);
	}
}
int main()
{
	freopen("telemetry.in", "r", stdin);
	freopen("telemetry.out", "w", stdout);
	
	int n, k;
	cin >> n >> k;
	vector <string> start(1, "");
	build(start, n, k);
	return 0;
}