#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value, y;
	int cnt = 1;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

int cnt(Node* t)
{
	return t ? t->cnt : 0;
}

void recalc(Node*& t)
{
	if (t) { t->cnt = cnt(t->left) + cnt(t->right) + 1; }
}

pair<Node*, Node*> split(Node* tree, int x)
{
	if (tree == nullptr) { return { nullptr, nullptr }; }
	if (x < tree->value)
	{
		auto p = split(tree->left, x);
		tree->left = p.second;
		recalc(p.first);
		recalc(tree);
		return { p.first, tree };
	}
	else
	{
		auto p = split(tree->right, x);
		tree->right = p.first;
		recalc(tree);
		recalc(p.second);
		return { tree, p.second };
	}
}

Node* merge(Node* a, Node* b)
{
	if (!a) { return b; }
	if (!b) { return a; }
	if (a->value > b->value) { swap(a, b); }
	if (a->y > b->y)
	{
		a->right = merge(a->right, b);
		recalc(a->right);
		recalc(a);
		return a;
	}
	else
	{
		b->left = merge(a, b->left);
		recalc(b->left);
		recalc(b);
		return b;
	}
}

Node* insert(Node* a, Node* node)
{
	if (!a) { return node; }
	if (node->y > a->y)
	{
		auto p = split(a, node->value);
		node->left = p.first;
		node->right = p.second;
		recalc(node);
		return node;
	}
	else
	{
		if (node->value < a->value)
		{
			a->left = insert(a->left, node);
			recalc(a->left);
		}
		else if (node->value > a->value)
		{
			a->right = insert(a->right, node);
			recalc(a->right);
		}
		recalc(a);
		return a;
	}
}

void erase(Node*& a, int x)
{
	if (!a) { return; }
	if (a->value == x)
	{
		a = merge(a->left, a->right);
	}
	else
	{
		if (a->value < x)
		{
			erase(a->right, x);
			recalc(a->right);
		}
		else
		{
			erase(a->left, x);
			recalc(a->left);
		}
	}
	recalc(a);
}

Node* exists(Node* node, int x)
{
	if (node == nullptr) { return nullptr; }
	if (node->value == x) { return node; }
	if (x < node->value)
	{
		return exists(node->left, x);
	}
	else
	{
		return exists(node->right, x);
	}
}

Node* parent = nullptr;

Node* next(int x)
{
	Node* curr = parent;
	Node* s = nullptr;
	while (curr != nullptr)
	{
		if (curr->value > x)
		{
			s = curr;
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	return s;
}

Node* prev(int x)
{
	Node* curr = parent;
	Node* s = nullptr;
	while (curr != nullptr)
	{
		if (curr->value < x)
		{
			s = curr;
			curr = curr->right;
		}
		else
		{
			curr = curr->left;
		}
	}
	return s;
}


Node* maximum(Node* t)
{
	while (t->right) { t = t->right; }
	return t;
}


int k_max(Node* t, int k)
{
	if (k <= cnt(t->right))
	{
		return k_max(t->right, k);
	}
	else
	{
		k -= cnt(t->right);
		if (k == 1)
		{
			return t->value;
		}
		else
		{
			k--;
			return k_max(t->left, k);
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
	
	for (int i = 0; i < n; i++)
	{
		int op, k;
		cin >> op >> k;
		if (op == 1)
		{
			Node* m = new Node;
			m->value = k;
			m->y = rand();
			parent = insert(parent, m);
		}
		else if (op == 0)
		{
			cout << k_max(parent, k) << '\n';
		}
		else if (op == -1)
		{
			erase(parent, k);
		}
	}

	return 0;
}