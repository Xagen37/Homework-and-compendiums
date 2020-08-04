#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cctype>
#include <string>

using namespace std;

int main()
{
	ifstream in("useless.in");
	ofstream out("useless.out");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	unordered_map <unsigned char, vector <string>> rules;
	set <unsigned char> non_ters;
	string input;
	getline(in, input);
	istringstream to_parse(input);
	int n; to_parse >> n;
	unsigned char start; to_parse >> start;
	non_ters.insert(start);

	while (getline(in, input))
	{
		istringstream to_parse(input);
		unsigned char non_ter; to_parse >> non_ter;
		non_ters.insert(non_ter);
		string arrow; to_parse >> arrow;
		string result; to_parse >> result;
		rules[non_ter].push_back(result);
		for (char ch : result)
		{
			if (!islower(ch))
			{
				non_ters.insert(ch);
			}
		}
	}

	unordered_set <unsigned char> generating, next_generating;
	while (true)
	{
		for (auto& it : rules)
		{
			for (auto& str : it.second)
			{
				bool just_term = true;
				bool only_generating = true;
				for (int i = 0; i < str.size(); i++)
				{
					if (!islower(str[i]))
					{
						just_term = false;
						if (!generating.count(str[i]))
						{
							only_generating = false;
							break;
						}
					}
				}
				if (just_term || only_generating)
				{
					next_generating.insert(it.first);
				}
			}
		}
		if (generating != next_generating)
		{
			generating = next_generating;
			next_generating.clear();
		}
		else
		{
			break;
		}
	}

	unordered_set <unsigned char> reachable, next_reachable;
	if (generating.count(start)) { reachable.insert(start); }
	while (true)
	{
		if (generating.count(start)) { next_reachable.insert(start); }
		for (auto& it : generating)
		{
			if (!reachable.count(it)) { continue; }
			const auto& copy = rules[it];
			for (auto& str : copy)
			{
				bool all_generating = true;
				set <char> temp;
				for (int i = 0; i < str.size(); i++)
				{
					if (!islower(str[i]))
					{
						if (generating.count(str[i])) { temp.insert(str[i]); }
						else { all_generating = false; }
					}
				}
				if (all_generating)
				{
					next_reachable.insert(temp.begin(), temp.end());
				}
			}
		}
		if (next_reachable != reachable)
		{
			reachable = next_reachable;
			next_reachable.clear();
		}
		else
		{
			break;
		}
	}

	for (char ch : non_ters)
	{
		if (!reachable.count(ch))
		{
			out << ch << ' ';
		}
	}
	
	return 0;
}