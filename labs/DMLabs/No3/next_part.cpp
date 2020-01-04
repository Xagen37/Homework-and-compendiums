#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main()
{
	freopen("nextpartition.in", "r", stdin);
	freopen("nextpartition.out", "w", stdout);
	string in;
	cin >> in;
	int n = 0;
	int i = 0;
	while (in[i] != '=')
	{
		n *= 10;
		n += (in[i] - '0');
		i++;
	}
	vector<int> prev;
	i++;
	while (i < in.length())
	{
		int k = 0;
		while (i < in.length() && in[i] != '+')
		{
			k *= 10;
			k += (in[i] - '0');
			i++;
		}
		prev.push_back(k);
		i++;
	}
	if (prev.size() < 2)
	{
		cout << "No solution";
		return 0;
	}
	//int shrt = prev.size() - 1;
	prev[prev.size() - 1]--;
	prev[prev.size() - 2]++;
	if (prev[prev.size() - 2] > prev[prev.size() - 1])
	{
		prev[prev.size() - 2] += prev[prev.size() - 1];
		prev.erase(prev.end() - 1);
	}
	else
	{
		while (prev[prev.size() - 2] * 2 <= prev[prev.size() - 1])
		{
			prev.push_back(prev[prev.size() - 1] - prev[prev.size() - 2]);
			prev[prev.size() - 2] = prev[prev.size() - 3];
		}
	}
	cout << n << '=' << prev[0];
	for (int i = 1; i < prev.size(); i++)
	{
		cout << '+' << prev[i];
	}
	return 0;
}