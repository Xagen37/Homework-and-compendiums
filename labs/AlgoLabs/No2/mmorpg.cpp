#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <int> st;
	vector <string> answ;
	vector <int> res;
	for (int i = 0; i < n; i++)
	{
		int val;
		cin >> val;
		if (st.empty())
		{
			st.push_back(val);
			answ.push_back("push");
		}
		else
		{
			if (val <= st.back())
			{
				st.push_back(val);
				answ.push_back("push");
			}
			else
			{
				while (!st.empty() && val > st.back())
				{
					res.push_back(st.back());
					st.pop_back();
					answ.push_back("pop");
				}
				st.push_back(val);
				answ.push_back("push");
			}
		}
	}
	while (!st.empty())
	{
		res.push_back(st.back());
		st.pop_back();
		answ.push_back("pop");
	}
	for (int i = 0; i < res.size() - 1; i++)
	{
		if (res[i] > res[i + 1])
		{
			cout << "impossible";
			return 0;
		}
	}
	for (int i = 0; i < answ.size(); i++)
	{
		cout << answ[i] << '\n';
	}
	return 0;
	return 0;
}