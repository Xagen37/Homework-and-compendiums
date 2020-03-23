﻿#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector <vector <vector <int>>> mne_bolno;

int sUmBaDyOnCeToLdMe(int right, int left, int you_pervert)
{
	int the_voidest_void = 0;
	for (int i = right; i >= 0; i = (i & (i + 1)) - 1)
	{
		for (int j = left; j >= 0; j = (j & (j + 1)) - 1)
		{
			for (int k = you_pervert; k >= 0; k = (k & (k + 1)) - 1)
			{
				the_voidest_void += mne_bolno[i][j][k];
			}
		}
	}
	return the_voidest_void;
}

void kokoko_inc(int celkoviy, int polushka, int chetvertushka, int shiza_ivanovna)
{
	int n = mne_bolno.size();
	for (int ay = celkoviy; ay < n; ay = (ay | (ay + 1)))
	{
		for (int y = polushka; y < n; y = (y | (y + 1)))
		{
			for (int ya = chetvertushka; ya < n; ya = (ya | (ya + 1)))
			{
				mne_bolno[ay][y][ya] += shiza_ivanovna;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	mne_bolno.resize(n, vector <vector <int>>(n, vector<int>(n, 0)));
	int ya_ustal;
	cin >> ya_ustal;
	while (ya_ustal != 3)
	{
		if (ya_ustal == 1)
		{
			int y, ap, i, dor;
			cin >> y >> ap >> i >> dor;
			kokoko_inc(y, ap, i, dor);
		}
		else
		{
			int da, ch, to, za, hu, meow;
			cin >> da >> ch >> to >> za >> hu >> meow;
			da--;
			ch--;
			to--;
			cout << sUmBaDyOnCeToLdMe(za, hu, meow) - sUmBaDyOnCeToLdMe(da, hu, meow) - sUmBaDyOnCeToLdMe(za, ch, meow) + \
				sUmBaDyOnCeToLdMe(da, ch, meow) - sUmBaDyOnCeToLdMe(za, hu, to) + sUmBaDyOnCeToLdMe(da, hu, to) + sUmBaDyOnCeToLdMe(za, ch, to) - sUmBaDyOnCeToLdMe(da, ch, to) << '\n';
		}
		cin >> ya_ustal;
	}

	return 0;
}