#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

unordered_set <string> is_inserted;
vector <string> codes;

void build(string prev)
{
	string postfix = prev.substr(1);
	if (is_inserted.find(postfix + '1') == is_inserted.end())
	{
		codes.push_back(postfix + '1');
		is_inserted.insert(postfix + '1');
		build(postfix + '1');
	}
	else if (is_inserted.find(postfix + '0') == is_inserted.end())
	{
		codes.push_back(postfix + '0');
		is_inserted.insert(postfix + '0');
		build(postfix + '0');
	}
	else
	{
		return;
	}
}

int main()
{
	freopen("chaincode.in", "r", stdin);
	freopen("chaincode.out", "w", stdout);

	int n;
	cin >> n;
	string start;
	for (int i = 0; i < n; i++)
	{
		start += '0';
	}
	codes.push_back(start);
	is_inserted.insert(start);
	build(start);
	for (int i = 0; i < codes.size(); i++)
	{
		cout << codes[i] << '\n';
	}
	return 0;
}