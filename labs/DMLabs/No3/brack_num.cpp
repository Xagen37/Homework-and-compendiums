#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int main()
{
	freopen("brackets2num.in", "r", stdin);
	freopen("brackets2num.out", "w", stdout);
    
	string in;
	cin >> in;
	int n = in.length() / 2;
	vector <vector <long long int>> br(2 * n + 1, vector <long long int>(2 * n + 1, 0));
	br[0][0] = 1;
	for (int i = 1; i <= 2 * n; i++)
	{
		for (int j = 0; j < 2 * n; j++)
		{
			if (j > 0)
			{
				br[i][j] += br[i - 1][j - 1];
			}
			if (j < 2 * n - 1)
			{
				br[i][j] += br[i - 1][j + 1];
			}
		}
	}

	long long int answ = 0;
	int balance = 0;
	for (int i = 0; i < in.length(); i++)
	{
		if (in[i] == '(')
		{
			balance++;
		}
		else
		{
			answ += br[in.length() - i - 1][balance + 1];
			balance--;
		}
	}
	cout << answ;
	return 0;
}
