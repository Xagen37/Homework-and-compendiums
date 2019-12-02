#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node
{
public:
	int m_par;
	int m_min;
	int m_max;
	int m_num;

	Node(int par, int min, int max, int num):
		m_par(par),
		m_min(min),
		m_max(max),
		m_num(num)
	{}
};

vector <Node> a;

int find(int x)
{
	Node & c = a[x];
	if (c.m_par != x)
	{
		return c.m_par = find(c.m_par);
	}
	return x;
}

void USSR(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y)
	{
		return;
	}
	if (a[x].m_num < a[y].m_num)
	{
		swap(x, y);
	}
	a[y].m_par = x;
	a[x].m_num += a[y].m_num;
	a[x].m_max = max(a[y].m_max, a[x].m_max);
	a[x].m_min = min(a[y].m_min, a[x].m_min);

	/*Node * l = &a[x];
	Node * r = &a[y];
	if (l->m_num > r->m_num)
	{
		Node* tmp = l;
		l = r;
		r = tmp;
	}
	l->m_par = y;
	r->m_max = max(r->m_max, l->m_max);
	r->m_min = min(r->m_min, l->m_min);
	r->m_num = r->m_num + l->m_num;*/
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		a.push_back(Node(i, i, i, 1));
	}

	string s;
	while (cin >> s)
	{
		if (s == "union")
		{
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			USSR(l, r);
		}
		else
		{
			int kek;
			cin >> kek;
			kek--;
			Node lol = a[find(kek)];
			cout << lol.m_min + 1 << ' ' << lol.m_max + 1 << ' ' << lol.m_num << '\n';
		}
	}

	return 0;
}
