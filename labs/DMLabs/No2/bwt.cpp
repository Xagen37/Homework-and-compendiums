#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	freopen("bwt.in", "r", stdin);
	freopen("bwt.out", "w", stdout);

	string s;
	cin >> s;
	int n = s.length();
	vector <string> shifts;
	shifts.push_back(s);
	for (int i = 0; i < n - 1; i++)
	{
		s = s.substr(1) + s[0];
		shifts.push_back(s);
	}

	sort(shifts.begin(), shifts.end());
	for (int i = 0; i < shifts.size(); i++)
	{
		cout << shifts[i].back();
	}

	return 0;
}