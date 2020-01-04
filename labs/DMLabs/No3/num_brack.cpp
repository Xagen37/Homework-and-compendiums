#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int main()
{
	freopen("num2brackets.in", "r", stdin);
	freopen("num2brackets.out", "w", stdout);

	long long int n, k;
	cin >> n >> k;
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
	string answ;
	int balance = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		if (br[2 * n - i - 1][balance + 1] > k)
		{
			answ += '(';
			balance++;
		}
		else
		{
			k -= br[2 * n - i - 1][balance + 1];
			answ += ')';
			balance--;
		}
	}
	cout << answ;
	return 0;
}