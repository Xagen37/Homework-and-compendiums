﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

vector <int> arr;
vector <int> tree;
vector <int> set;
vector <bool> is_set;

bool comp_less(const pair<pair<int, int>, int>& left, const pair<pair<int, int>, int>& right)
{
	return left.second < right.second;
}

void build(int x, int lx, int rx, vector <int>& arr, vector <int> & tree)
{
	if (rx - lx <= 1)
	{
		if (lx < arr.size())
		{
			tree[x] = arr[lx];
		}
		else
		{
			tree[x] = INT_MAX;
		}
		return;
	}

	int m = lx + (rx - lx) / 2;
	build(2 * x + 1, lx, m, arr, tree);
	build(2 * x + 2, m, rx, arr, tree);
	 
	tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
}

void propagate(int x, int lx, int rx)
{
	if (rx - lx <= 1)
	{
		is_set[x] = 0;
		return;
	}
	if (!is_set[x]) { return; }

	int m = lx + (rx - lx) / 2;
	is_set[2 * x + 1] = true;
	set[2 * x + 1] = set[x];
	tree[2 * x + 1] = set[x];
	is_set[2 * x + 2] = true;
	set[2 * x + 2] = set[x];
	tree[2 * x + 2] = set[x];

	is_set[x] = false;
}

void fset(int x, int lx, int rx, int left, int right, int val)
{
	propagate(x, lx, rx);
	if (lx >= right || rx <= left) { return; }
	if (lx >= left && rx <= right)
	{
		is_set[x] = true;
		set[x] = val;
		tree[x] = val;
		return;
	}
	int m = lx + (rx - lx) / 2;
	fset(2 * x + 1, lx, m, left, right, val);
	fset(2 * x + 2, m, rx, left, right, val);
	tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
}

int quest(int x, int lx, int rx, int left, int right)
{
	propagate(x, lx, rx);
	//if (rx - lx <= 1) { return tree[x]; }
	if (lx >= right || rx <= left) { return INT_MAX; }
	if (lx >= left && rx <= right) { return tree[x]; }
	int m = lx + (rx - lx) / 2;
	int m1 = quest(2 * x + 1, lx, m, left, right);
	int m2 = quest(2 * x + 2, m, rx, left, right);

	return min(m1, m2);
}

int main()
{
	freopen("rmq.in", "r", stdin);
	freopen("rmq.out", "w", stdout);

	/*ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);*/

	int n, m;
	cin >> n >> m;

	int pow = 1;
	while (pow < n) { pow = (pow << 1); }
	
	tree.resize(2 * pow, INT_MAX);
	arr.resize(n, INT_MAX);
	set.resize(2 * pow, 0);
	is_set.resize(2 * pow, 0);
	vector <pair<pair<int, int>, int>> queries(m);
	for (int i = 0; i < m; i++)
	{
		int l, r, q;
		cin >> l >> r >> q;
		l--;
		queries[i] = { {l, r}, q };
	}
	sort(queries.begin(), queries.end(), comp_less);

	for (int i = 0; i < queries.size(); i++)
	{
		fset(0, 0, pow, queries[i].first.first, queries[i].first.second, queries[i].second);
	}

	for (int i = 0; i < m; i++)
	{
		if (quest(0, 0, pow, queries[i].first.first, queries[i].first.second) != queries[i].second)
		{
			cout << "inconsistent";
			return 0;
		}
	}

	cout << "consistent\n";
	for (int i = 0; i < n; i++)
	{
		cout << quest(0, 0, pow, i, i + 1) << ' ';
	}
	return 0;
}