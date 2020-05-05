#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node
{
	int priority = 1, value = 0, cnt = 1;
	bool revert = false;
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

void push(Node*& t)
{
	if (t != nullptr && t->revert)
	{
		t->revert = false;
		swap(t->left, t->right);
		if (t->left != nullptr) { t->left->revert ^= 1; }
		if (t->right != nullptr) { t->right->revert ^= 1; }
	}
}

Node* merge(Node* t1, Node* t2)
{
	push(t1);
	push(t2);
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
	push(t);
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

void reverse(Node*& t, int lpos, int rpos)
{
	auto p = split(t, lpos);
	auto p2 = split(p.second, rpos - lpos + 1);
	p2.first->revert ^= 1;
	t = merge(merge(p.first, p2.first), p2.second);
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

void output(Node* t, vector <int>& answ) {
	if (!t) { return; }
	push(t);
	output(t->left, answ);
	answ.push_back(t->value);
	output(t->right, answ);
}

void output(Node* t) {
	if (!t)  return;
	push(t);
	output(t->left);
	cout << t->value << ' ';
	output(t->right);
}

int main()
{
	int n, m;
	cin >> n >> m;
	Node* parent = nullptr;
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
		reverse(parent, l, r);
	}

	vector <int> answ;
	output(parent, answ);
	//cout << answ.size() << '\n';
	for (int i = 0; i < answ.size(); i++)
	{
		cout << answ[i] << ' ';
	}
	return 0;
}