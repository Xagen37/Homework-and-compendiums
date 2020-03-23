﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>

using namespace std;

class Node
{
public:
	const static int E = INT_MIN;
	Node* left, * right;
	int value_max, value_sum;
	int to_add;

	Node() :
		left(nullptr),
		right(nullptr),
		value_max(E),
		value_sum(E),
		to_add(0)
	{}

	Node(int v_max, int v_sum, int add) :
		left(0),
		right(0),
		value_max(v_max),
		value_sum(v_sum),
		to_add(add)
	{}

	~Node()
	{
		if (left != nullptr)
		{
			delete left;
		}
		if (right != nullptr)
		{
			delete right;
		}
	}

};

class Tree
{
	Node* m_root;
	const static int border = (1 << 30);

	void propagate(Node*& v, int lx, int rx)
	{
		if (rx - lx <= 1)
		{
			v->to_add = INT_MIN;
			return;
		}

		int mx = lx + (rx - lx) / 2;
		if (v->left == 0)
		{
			v->left = new Node(0, 0, v->to_add);
		}
		push(v->left, v->to_add, mx - lx);

		if (v->right == 0)
		{
			v->right = new Node(0, 0, v->to_add);
		}
		push(v->right, v->to_add, mx - lx);

		v->to_add = INT_MIN;
	}

	void push(Node*& v, int add, int length)
	{
		if (add != INT_MIN)
		{
			v->value_sum = length * add;
			v->value_max = (add < 0) ? 0 : v->value_sum;
			v->to_add = add;
		}
	}

	void set(int lx, int rx, Node*& v, int left, int right, int d)
	{
		if (lx >= right || rx <= left) { return; }
		if (rx - lx < 1) { return; }

		if (lx >= left && rx <= right) 
		{
			push(v, d, rx - lx);
			return;
		}
		propagate(v, lx, rx);

		int mx = lx + (rx - lx) / 2;
		set(lx, mx, v->left, left, right, d);
		set(mx, rx, v->right, left, right, d);

		v->value_sum = v->left->value_sum + v->right->value_sum;
		v->value_max = max(v->left->value_max, v->left->value_sum + v->right->value_max);
	}

	int quest(int height, Node*& v)
	{
		Node* copy = v;
		if (copy->value_max <= height)
		{
			return INT_MAX;
		}
		int left = 0, right = border, mid;
		while (copy)
		{
			propagate(copy, left, right);
			mid = left + (right - left) / 2;
			if (copy->left == 0) { break; }

			if (copy->left->value_max <= height)
			{
				height -= copy->left->value_sum;
				left = mid;
				copy = copy->right;
			}
			else
			{
				right = mid;
				copy = copy->left;
			}
		}
		return --left;
	}

public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void set(int left, int right, int d)
	{
		set(0, border, m_root, left, right, d);
	}

	int quest(int height)
	{
		return quest(height, m_root);
	}

	~Tree()
	{
		if (m_root != nullptr)
		{
			delete m_root;
		}
	}
};

int main()
{
	int n;
	cin >> n;
	Tree tree(new Node(0, 0, INT_MIN));
	char in;
	cin >> in;
	while (in != 'E')
	{
		if (in == 'Q')
		{
			int h;
			cin >> h;
			int answ = tree.quest(h);
			cout << min(answ, n);
			cout << '\n';
		}
		else
		{
			int a, b, d;
			cin >> a >> b >> d;
			b++;
			tree.set(a, b, d);
		}
		cin >> in;
	}

	return 0;
}