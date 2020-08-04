#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int id = 0;
	bool is_allowing = false;
	unordered_map<char, int> edges;
};

bool bfs_check(vector <Node> & a, vector <Node> & b)
{
	set<pair<int, int>> used;
	queue <pair <Node, Node>> q;
	q.push({ a[1], b[1] });
	used.insert({ 1, 1 });
	while (!q.empty())
	{
		auto p = q.front(); q.pop();
		if (p.first.is_allowing != p.second.is_allowing)
		{
			return false;
		}
		for (char c = 'a'; c <= 'z'; c++)
		{
			Node a_next, b_next;
			bool flag = true;
			if (p.first.edges.find(c) != p.first.edges.end())
			{
				a_next = a[p.first.edges[c]];
			}
			else { flag = false; }

			if (p.second.edges.find(c) != p.second.edges.end())
			{
				b_next = b[p.second.edges[c]];
				if (!flag) { return false; }
			}
			else { if (flag) { return false; } }

			if (used.find({a_next.id, b_next.id}) == used.end())
			{
				used.insert({ a_next.id, b_next.id });
				q.push({ a_next, b_next });
			}
		}
	}
	return true;
}

int main()
{
	//freopen("isomorphism.in", "r", stdin);
	//freopen("isomorphism.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
//--------------------------------------------------------------
	int n1, m1, k1;
	cin >> n1 >> m1 >> k1;
	vector <Node> two_a(n1 + 1);
	for (int i = 1; i <= n1; i++)
	{
		two_a[i].id = i;
	}
	for (int i = 0; i < k1; i++)
	{
		int id;
		cin >> id;
		two_a[id].is_allowing = true;
	}
	for (int i = 0; i < m1; i++)
	{
		int from, to; char c;
		cin >> from >> to >> c;
		two_a[from].edges[c] = to;
	}
//------------------------------------------------------------------
	int n2, m2, k2;
	cin >> n2 >> m2 >> k2;
	vector <Node> two_b(n2 + 1);
	for (int i = 1; i <= n2; i++)
	{
		two_b[i].id = i;
	}
	for (int i = 0; i < k2; i++)
	{
		int id;
		cin >> id;
		two_b[id].is_allowing = true;
	}
	for (int i = 0; i < m2; i++)
	{
		int from, to; char c;
		cin >> from >> to >> c;
		two_b[from].edges[c] = to;
	}
//-----------------------------------------------------------------------
	if (bfs_check(two_a, two_b))
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}

	return 0;
}
