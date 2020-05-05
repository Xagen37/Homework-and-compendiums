#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node
{
	int priority = 1, value = 0, cnt = 1;
	Node* left = nullptr;
	Node* right = nullptr;
};

int cnt(Node* it)
{
	return it ? it->cnt : 0;
}

void upd_cnt(Node* it)
{
	if (it)
	{
		it->cnt = cnt(it->left) + cnt(it->right) + 1;
	}
}

Node* merge(Node* t1, Node* t2)
{
	if (!t2) { return t1; }
	if (!t1) { return t2; }
	if (t1->priority > t2->priority)
	{
		t1->right = merge(t1->right, t2);
		upd_cnt(t1);
		return t1;
	}
	else
	{
		t2->left = merge(t1, t2->left);
		upd_cnt(t2);
		return t2;
	}
}


pair<Node*, Node*> split(Node* t, int k)
{
	if (t == nullptr)
	{
		return { nullptr, nullptr };
	}
	int l = cnt(t->left);
	if (l >= k)
	{
		auto p = split(t->left, k);
		t->left = p.second;
		upd_cnt(t);
		return { p.first, t };
	}
	else
	{
		auto p = split(t->right, k - l - 1);
		t->right = p.first;
		upd_cnt(t);
		return { t, p.second };
	}
}

void insert(Node*& t, int pos, int val)
{
	auto p = split(t, pos);
	Node* n = new Node;
	n->value = val;
	n->priority = rand();
	p.first = merge(p.first, n);
	t = merge(p.first, p.second);
}

void remove(Node*& t, int pos)
{
	auto p = split(t, pos);
	auto p2 = split(p.second, 1);
	t = merge(p.first, p2.second);
}

void move_to_begin(Node*& t, int lpos, int rpos)
{
	auto p = split(t, lpos);
	auto p2 = split(p.second, rpos - lpos + 1);
	t = merge(merge(p2.first, p.first), p2.second);
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

int main()
{
	Node* parent = nullptr;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		insert(parent, i, i + 1);
	}
	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		move_to_begin(parent, l, r);
		//output(parent);
		//cout << endl;
	}

	vector <int> answ;
	output(parent, answ);
	for (int i = 0; i < answ.size(); i++)
	{
		cout << answ[i] << ' ';
	}
}
