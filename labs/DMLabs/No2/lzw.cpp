#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	freopen("lzw.in", "r", stdin);
	freopen("lzw.out", "w", stdout);

	map <string, int> list;
	for (char c = 'a'; c <= 'z'; c++)
	{
		string tmp;
		tmp.push_back(c);
		list[tmp] = c - 'a';
	}
	int cnt = 26;

	string s;
	cin >> s;
	string buff;
	//buff.push_back(s.front());
	for (int i = 0; i < s.length(); i++)
	{
		string t = buff + s[i];
		if (list.find(t) == list.end())
		{
			cout << list[buff] << ' ';
			list[t] = cnt;
			cnt++;
			buff = "";
			buff.push_back(s[i]);
		}
		else
		{
			buff = t;
		}
	}
	cout << list[buff];
	return 0;
}