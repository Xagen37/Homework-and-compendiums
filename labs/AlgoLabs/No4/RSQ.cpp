﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Node
{
	Node* m_left, * m_right;
	long long int m_value;
	int m_lx, m_rx;

public:
	Node() :
		m_left(nullptr),
		m_right(nullptr),
		m_value(0),
		m_lx(0),
		m_rx(0)
	{}

	Node(long long int value = 0, int lx = 0, int rx = 0, Node* left = nullptr, Node* right = nullptr) :
		m_left(left),
		m_right(right),
		m_value(value),
		m_lx(lx),
		m_rx(rx)
	{}

	long long int value()
	{
		return m_value;
	}

	Node* left()
	{
		return m_left;
	}

	Node* right()
	{
		return m_right;
	}

	int l_border()
	{
		return m_lx;
	}

	int r_border()
	{
		return m_rx;
	}

	void set_value(long long int value)
	{
		m_value = value;
	}

	void set_left(Node* left)
	{
		m_left = left;
	}

	void set_right(Node* right)
	{
		m_right = right;
	}

	int mid()
	{
		return m_lx + (m_rx - m_lx) / 2;
	}

	void refresh()
	{
		m_value = m_left->value() + m_right->value();
	}

	~Node()
	{
		if (m_left != nullptr)
		{
			delete m_left;
		}
		if (m_right != nullptr)
		{
			delete m_right;
		}
	}

};

class Tree
{
	Node* m_root;

	void build(vector <long long int>& arr, Node*& v)
	{
		if (v->r_border() - v->l_border() <= 1)
		{
			if (v->l_border() < arr.size())
			{
				v->set_value(arr[v->l_border()]);
			}
			return;
		}

		v->set_left(new Node(0, v->l_border(), v->mid()));
		v->set_right(new Node(0, v->mid(), v->r_border()));
		Node* left = v->left();
		Node* right = v->right();
		build(arr, left);
		build(arr, right);
		v->refresh();
	}

	void set(int dest, long long int val, Node*& v)
	{
		if (v->r_border() - v->l_border() <= 1)
		{
			v->set_value(val);
			return;
		}

		if (dest < v->mid())
		{
			Node* left = v->left();
			set(dest, val, left);
		}
		else
		{
			Node* right = v->right();
			set(dest, val, right);
		}
		v->refresh();
	}

	long long int sum(int l, int r, Node* v)
	{
		if (l >= v->r_border() || r <= v->l_border())
		{
			return 0;
		}
		if (v->l_border() >= l && v->r_border() <= r)
		{
			return v->value();
		}
		long long int sum_l = sum(l, r, v->left());
		long long int sum_r = sum(l, r, v->right());
		return sum_l + sum_r;
	}
public:
	Tree(Node* root = nullptr):
		m_root(root)
	{}

	void build(vector<long long int> & arr)
	{
		build(arr, m_root);
	}

	void set(int dest, long long int val)
	{
		set(dest, val, m_root);
	}

	long long int sum(int left, int right)
	{
		return sum(left, right, m_root);
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
	vector <long long int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	Tree tree(new Node(0, 0, n));
	tree.build(a);


	string op;
	while (cin >> op)
	{
		if (op == "set")
		{
			long long int i, x;
			cin >> i >> x;
			tree.set(i - 1, x);
		}
		else
		{
			long long int i, j;
			cin >> i >> j;
			cout << tree.sum(i - 1, j) << '\n';
		}
	}


	return 0;
}