#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

int main()
{
	ifstream in("epsilon.in");
	ofstream out("epsilon.out");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	const string EPS = "epsilon";
	unordered_map <unsigned char, vector <string>> rules;
	unordered_map<unsigned char, bool> is_eps;
	string input;
	string rubbish;
	getline(in, rubbish);
	while (getline(in, input))
	{
		istringstream to_parse(input);
		unsigned char non_ter; to_parse >> non_ter;
		string arrow; to_parse >> arrow;
		string result; to_parse >> result;
		if (result.size())
		{
			rules[non_ter].push_back(result);
		}
		else
		{
			rules[non_ter].push_back(EPS);
		}
		is_eps[non_ter] = false;
	}

	set <unsigned char> epses, next_epses;
	for (auto& it : rules)
	{
		for (auto& str : it.second)
		{
			if (str == EPS)
			{
				epses.insert(it.first);
				is_eps[it.first] = true;
				break;
			}
		}
	}

	while (true)
	{
		for (auto& it : rules)
		{
			for (auto& str : it.second)
			{
				bool flag = true;
				for (int i = 0; i < str.size(); i++)
				{
					if (islower(static_cast<unsigned char>(str[i])) || !is_eps[str[i]])
					{
						flag = false;
						break;
					}
				}
				if (flag || str == EPS)
				{
					next_epses.insert(it.first);
					is_eps[it.first] = true;
				}
			}
		}
		if (next_epses != epses)
		{
			epses = next_epses;
		}
		else
		{
			break;
		}
	}

	for (auto& ch : epses)
	{
		out << ch << ' ';
	}

	return 0;
}