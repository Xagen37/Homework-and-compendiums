#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);

	long long int n;
	cin >> n;
	vector <long long int> p(n);
	for (long long int i = 0; i < n; i++)
	{
		cin >> p[i];
	}
	sort(p.begin(), p.end());
	vector <long long int> s;
	long long int pt0 = 0, pt1 = 1, st0 = 0, st1 = 1;
	vector <vector <long long int> > tree(n, vector <long long int>());
	s.push_back(p[pt0] + p[pt1]);
	tree.push_back(vector<long long int>({ pt0, pt1 }));
	pt0 += 2;
	pt1 += 2;
	
	while (pt0 < p.size() || st0 < s.size())
	{
		if (pt0 >= p.size() && (s.size() - st0 <= 1))
		{
			break;
		}

		if (pt1 < p.size() && p[pt1] <= s[st0])
		{
			s.push_back(p[pt0] + p[pt1]);
			tree.push_back(vector<long long int>({ pt0, pt1 }));
			pt0 += 2;
			pt1 += 2;
		}
		else if (pt0 < p.size() && (st1 >= s.size() || p[pt0] <= s[st1])
				&& (pt1 >= p.size() || p[pt1] > s[st0]))
		{
			s.push_back(p[pt0] + s[st0]);
			tree.push_back(vector<long long int>({ pt0, st0 + n }));
			pt0++;
			pt1++;
			st0++;
			st1++;
		}
		else
		{
			s.push_back(s[st0] + s[st1]);
			tree.push_back(vector <long long int>({ n + st0, n + st1 }));
			st0 += 2;
			st1 += 2;
		}
	}

	vector <long long int> d(tree.size(), -1);
	queue <long long int> q;
	d[tree.size() - 1] = 0;
	q.push(tree.size() - 1);
	while (!q.empty())
	{
		long long int c = q.front();
		q.pop();
		for (auto u : tree[c])
		{
			if (d[u] == -1)
			{
				d[u] = d[c] + 1;
				q.push(u);
			}
		}
	}

	long long int sum = 0;
	for (long long int i = 0; i < n; i++)
	{
		sum += (d[i] * p[i]);
	}
	cout << sum;
	return 0;
}