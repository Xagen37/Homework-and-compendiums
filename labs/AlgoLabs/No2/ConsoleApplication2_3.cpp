#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector <int> st;
	vector <int> st_min;
	for (int i = 0; i < n; i++)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			int val;
			cin >> val;
			st.push_back(val);
			if (st_min.empty())
			{
				st_min.push_back(val);
			}
			else
			{
				if (st_min.back() > val)
				{
					st_min.push_back(val);
				}
				else
				{
					st_min.push_back(st_min.back());
				}
			}
			break;
		}
		case 2: 
		{
			st.pop_back();
			st_min.pop_back();
			break;
		}
		case 3:
		{
			cout << st_min.back() << '\n';
			break;
		}
		default:
			break;
		}
	}
	return 0;
}