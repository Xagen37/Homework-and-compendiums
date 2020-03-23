﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Node
{
	Node* m_left, * m_right;
	long long int m_value;
	int m_lx, m_rx;
	long long int m_add, m_set;

public:
	static const long long int E = LLONG_MAX;

	Node() :
		m_left(nullptr),
		m_right(nullptr),
		m_value(0),
		m_lx(0),
		m_rx(0),
		m_add(0),
		m_set(E)
	{}

	Node(long long int value = 0, int lx = 0, int rx = 0, Node * left = nullptr, Node * right = nullptr) :
		m_left(left),
		m_right(right),
		m_value(value),
		m_lx(lx),
		m_rx(rx),
		m_add(0),
		m_set(E)
	{}

	long long int value()
	{
		return m_value;
	}

	Node*& left()
	{
		return m_left;
	}

	Node*& right()
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

	long long int mid()
	{
		return m_lx + ((long long int)m_rx - m_lx) / 2;
	}

	void set_set(long long int set)
	{
		m_set = set;
	}

	void set_add(long long int add)
	{
		m_add = add;
	}

	void refresh()
	{
		m_value = min(m_left->value(), m_right->value());
	}

	long long int set()
	{
		return m_set;
	}

	long long int add()
	{
		return m_add;
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
private:
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

		v->set_left(new Node(v->E, v->l_border(), v->mid()));
		v->set_right(new Node(v->E, v->mid(), v->r_border()));
		Node* left = v->left();
		Node* right = v->right();
		build(arr, left);
		build(arr, right);
		v->refresh();
	}

	void propagate(Node*& v)
	{
		if (v->r_border() - v->l_border() <= 1)
		{
			return;
		}
		if (v->set() == v->E)
		{
			if (!v->add()) { return; }
			v->left()->set_add(v->left()->add() + v->add());
			v->left()->set_value(v->left()->value() + v->add());
			v->right()->set_add(v->right()->add() + v->add());
			v->right()->set_value(v->right()->value() + v->add());
			v->set_add(0);
			//v->refresh();
			return;
		}
		v->left()->set_set(v->set());
		v->left()->set_add(v->add());
		v->left()->set_value(v->set() + v->add());
		v->right()->set_set(v->set());
		v->right()->set_add(v->add());
		v->right()->set_value(v->set() + v->add());
		v->set_set(v->E);
		v->set_add(0);
		v->refresh();
	}

	void set(int l, int r, long long int val, Node*& v)
	{
		propagate(v);
		if (v->l_border() >= r || v->r_border() <= l) { return; }
		if (v->l_border() >= l && v->r_border() <= r)
		{
			v->set_set(val);
			v->set_add(0);
			v->set_value(val);
			return;
		}
		set(l, r, val, v->left());
		set(l, r, val, v->right());
		v->refresh();
	}

	long long int sum(int l, int r, Node* v)
	{
		propagate(v);
		if (l >= v->r_border() || r <= v->l_border())
		{
			return v->E;
		}
		if (v->l_border() >= l && v->r_border() <= r)
		{
			return v->value();
		}
		long long int sum_l = sum(l, r, v->left());
		long long int sum_r = sum(l, r, v->right());
		return min(sum_l, sum_r);
	}

	void add(int l, int r, long long int val, Node* v)
	{
		propagate(v);
		if (l >= v->r_border() || r <= v->l_border())
		{
			return;
		}
		if (v->l_border() >= l && v->r_border() <= r)
		{
			v->set_add(v->add() + val);
			v->set_value(v->value() + val);
			return;
		}
		add(l, r, val, v->left());
		add(l, r, val, v->right());
		v->refresh();
	}
public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void build(vector<long long int>& arr)
	{
		build(arr, m_root);
	}

	void set(int left, int right, long long int val)
	{
		set(left, right, val, m_root);
	}

	long long int sum(int left, int right)
	{
		return sum(left, right, m_root);
	}

	void add(int left, int right, long long int val)
	{
		return add(left, right, val, m_root);
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
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector <long long int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	Tree tree(new Node(Node::E, 0, n));
	tree.build(a);

	string in;
	while (cin >> in)
	{
		if (in == "min")
		{
			int i, j;
			cin >> i >> j;
			cout << tree.sum(i - 1, j) << '\n';
		}
		else if (in == "set")
		{
			long long int i, j, val;
			cin >> i >> j >> val;
			tree.set(i - 1, j, val);
		}
		else
		{
			long long int i, j, val;
			cin >> i >> j >> val;
			tree.add(i - 1, j, val);
		}
	}

	return 0;
}