#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector <int> st;
	char c;
	while (cin >> c)
	{
		switch (c)
		{
		case '+':
		{
			int l = st.back();
			st.pop_back();
			int r = st.back();
			st.pop_back();

			st.push_back(l + r);
			break;
		}
		case '-':
		{
			int l = st.back();
			st.pop_back();
			int r = st.back();
			st.pop_back();

			st.push_back(r - l);
			break;
		}
		case '*':
		{
			int l = st.back();
			st.pop_back();
			int r = st.back();
			st.pop_back();

			st.push_back(l * r);
			break;
		}
		default:
			st.push_back(c - '0');
			break;
		}
	}
	cout << st.back();
	return 0;
}