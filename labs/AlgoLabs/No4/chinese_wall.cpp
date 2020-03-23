﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
//#define int long long

using namespace std;

class Node
{
public:
	const static int E = INT_MAX;
	Node* left, * right;
	int value;
	int pos;
	int lx, rx;
	int set;
	bool is_set;

	Node() :
		left(nullptr),
		right(nullptr),
		value(E),
		pos(E),
		lx(0),
		rx(0),
		set(E),
		is_set(false)
	{}

	Node(int ival = E, int ilx = 0, int irx = 0, Node * ileft = nullptr, Node * iright = nullptr) :
		left(ileft),
		right(iright),
		value(ival),
		pos(E),
		lx(ilx),
		rx(irx),
		set(E),
		is_set(false)
	{}

	int mid()
	{
		return (rx + lx) / 2;
	}

	void refresh()
	{
		if (left->value < right->value)
		{
			value = left->value;
			pos = left->pos;
		}
		else if (left->value > right->value)
		{
			value = right->value;
			pos = right->pos;
		}
		else
		{
			value = left->value;
			pos = min(left->pos, right->pos);
		}
	}

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

	void build(vector <int>& arr, Node*& v)
	{
		if (v->rx - v->lx <= 1)
		{
			if (v->lx < arr.size())
			{
				v->value = arr[v->lx];
				v->pos = v->lx;
			}
			else
			{
				v->value = v->E;
				v->pos = v->E;
			}
			return;
		}

		v->left = new Node(v->E, v->lx, v->mid());
		v->right = new Node(v->E, v->mid(), v->rx);
		Node* left = v->left;
		Node* right = v->right;
		build(arr, left);
		build(arr, right);
		v->refresh();
	}

	void propagate(Node*& v)
	{
		if (v->rx - v->lx <= 1) { v->is_set = false; return; }
		if (!v->is_set) { return; }

		if (v->left->value < v->set)
		{
			v->left->set = v->set;
			v->left->is_set = true;
			v->left->value = v->set;
		}
		if (v->right->value < v->set)
		{
			v->right->set = v->set;
			v->right->is_set = true;
			v->right->value = v->set;
		}
	
		v->is_set = false;
		v->refresh();
	}

	void set(int val, int left, int right, Node*& v)
	{
		propagate(v);
		if (v->lx >= right || v->rx <= left) { return; }
		if (v->lx >= left && v->rx <= right)
		{
			v->set = val;
			v->is_set = true;
			if (v->value < val)
			{
				v->value = val;
			}
			propagate(v);
			return;
		}
		set(val, left, right, v->left);
		set(val, left, right, v->right);
		propagate(v);
		v->refresh();
	}

	pair<int, int> quest(int left, int right, Node*& v)
	{
		propagate(v);
		if (v->rx <= left || v->lx >= right) { return { v->E, v->E }; }
		if (v->lx >= left && v->rx <= right) { return { v->value, v->pos }; }
		auto m1 = quest(left, right, v->left);
		auto m2 = quest(left, right, v->right);
		if (m1.first < m2.first)
		{
			return m1;
		}
		else if (m1.first > m2.first)
		{
			return m2;
		}
		else
		{
			return (m1.second < m2.second) ? m1 : m2;
		}
	}

public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void build(vector<int>& arr)
	{
		build(arr, m_root);
	}

	void set(int val, int left, int right)
	{
		set(val, left, right, m_root);
	}

	pair<int, int> quest(int left, int right)
	{
		return quest(left, right, m_root);
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
	int n, m;
	cin >> n >> m;
	vector <int> wall(n, 0);
	Tree tree(new Node(0, 0, n));
	tree.build(wall);
	for (int i = 0; i < m; i++)
	{
		string order;
		cin >> order;
		if (order == "defend")
		{
			int l, r, val;
			cin >> l >> r >> val;
			l--;
			tree.set(val, l, r);
		}
		else
		{
			int l, r;
			cin >> l >> r;
			l--;
			auto q = tree.quest(l, r);
			cout << q.first << ' ' << q.second + 1 << '\n';
		}
	}
	
	return 0;
}