#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <pair <int, int> > st;
	int color = -1, cnt = 0, sum = 0;
	bool is_pop = false;
	for (int i = 0; i < n; i++)
	{
		int ball;
		cin >> ball;
		if (ball == color)
		{
			cnt++;
		}
		else
		{
			if (is_pop)
			{
				auto prev = st.back();
				if (prev.first == color)
				{
					if (prev.second + cnt >= 3)
					{
						sum += (prev.second + cnt);
						st.pop_back();
						cnt = 1;
						color = ball;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				if (cnt >= 3)
				{
					is_pop = true;
					sum += cnt;
					cnt = 1;
					color = ball;
				}
				else
				{
					st.push_back({ color, cnt });
					color = ball;
					cnt = 1;
				}
			}
		}
	}

	if (!is_pop)
	{
		if (cnt >= 3)
		{
			sum += cnt;
		}
	}
	else if (!st.empty())
	{	
		if (st.back().first == color)
		{
			if (st.back().second + cnt >= 3)
			{
				sum += st.back().second + cnt;
			}
		}
	}
	cout << sum;
	return 0;
}