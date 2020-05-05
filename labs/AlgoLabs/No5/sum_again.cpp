#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

struct Node
{
	long long int value = 0, y = 0;
	long long int m_sum = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};


long long int sum(Node* t)
{
	if (t)
	{
		return t->m_sum;
	}
	else
	{
		return 0;
	}
}

void upd(Node* it)
{
	if (it)
	{
		it->m_sum = it->value +sum(it->left) + sum(it->right);
	}
}

Node* merge(Node* a, Node* b)
{
	if (!a) { return b; }
	if (!b) { return a; }
	if (a->value > b->value) { swap(a, b); }
	upd(a);
	upd(b);
	if (a->y > b->y)
	{
		a->right = merge(a->right, b);
		upd(a->right);
		upd(a);
		return a;
	}
	else
	{
		b->left = merge(a, b->left);
		upd(b->left);
		upd(b);
		return b;
	}
}


pair<Node*, Node*> split(Node* tree, int x)
{
	if (tree == nullptr) { return { nullptr, nullptr }; }
	upd(tree);
	if (x < tree->value)
	{
		auto p = split(tree->left, x);
		tree->left = p.second;
		upd(p.first);
		upd(tree);
		return { p.first, tree };
	}
	else
	{
		auto p = split(tree->right, x);
		tree->right = p.first;
		upd(p.second);
		upd(tree);
		return { tree, p.second };
	}
}

Node* insert(Node* a, Node* node)
{
	if (!a) { return node; }
	upd(a);
	auto p = split(a, node->value);
	return merge(p.first, merge(node, p.second));
}

void remove(Node*& t, int pos)
{
	auto p = split(t, pos);
	auto p2 = split(p.second, 1);
	t = merge(p.first, p2.second);
}

void output(Node* t, vector <int>& answ) {
	if (!t) { return; }
	output(t->left, answ);
	answ.push_back(t->value);
	output(t->right, answ);
}

void output(Node* t) {
	if (!t)  return;
	output(t->left);
	cout << t->value << ' ';
	output(t->right);
}

Node* exists(Node* t, long long int val)
{
	if (!t) { return nullptr; }
	if (t->value == val) { return t; }
	if (val < t->value)
	{
		return exists(t->left, val);
	}
	else
	{
		return exists(t->right, val);
	}
}


long long int sum_range(Node* t, long long int l, long long int r)
{
	if (l > r) { swap(l, r); }
	auto p = split(t, l - 1);
	auto p2 = split(p.second, r);
	long long int answ = sum(p2.first);
	t = merge(p.first, merge(p2.first, p2.second));
	return answ;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//srand(time(0)); nani

	int n;
	cin >> n;
	Node* parent = nullptr;
	long long int accum = 0;
	bool flag = false;
	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		if (c == '+')
		{
			long long int x;
			cin >> x;
			long long int value = flag ? (x + accum) % 1000000000LL : x;
			if (!exists(parent, value))
			{
				Node* m = new Node;
				m->value = value;
				m->y = rand();
				m->m_sum = m->value;
				parent = insert(parent, m);
			}
			accum = 0;
			flag = false;
		}
		else if (c == '?')
		{
			long long int l, r;
			cin >> l >> r;
			accum = sum_range(parent, l, r);
			cout << accum << '\n';
			flag = true;
		}
		//output(parent);
		//cout << endl;
	}
}