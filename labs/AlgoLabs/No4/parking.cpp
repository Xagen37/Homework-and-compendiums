﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>

using namespace std;

class Node
{
public:
	const static int E = 0;
	Node* left, * right;
	int value;
	int pos_l, pos_r;
	int lx, rx;
	int set;
	bool is_set;

	Node() :
		left(nullptr),
		right(nullptr),
		value(E),
		pos_l(INT_MAX),
		pos_r(INT_MIN),
		lx(0),
		rx(0),
		set(E),
		is_set(false)
	{}

	Node(int ival = E, int ilx = 0, int irx = 0, Node * ileft = nullptr, Node * iright = nullptr) :
		left(ileft),
		right(iright),
		value(ival),
		pos_l(INT_MAX),
		pos_r(INT_MIN),
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
		value = left->value + right->value;
		pos_l = min(left->pos_l, right->pos_l);
		pos_r = max(left->pos_r, right->pos_r);
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
				v->pos_l = v->lx;
				v->pos_r = v->lx;
			}
			else
			{
				v->value = v->E;
				v->pos_l = INT_MAX;
				v->pos_r = INT_MIN;
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

	int set(int pos, Node*& v)
	{
		int answ = INT_MAX;
		if (v == nullptr)
		{
			return answ;
		}
		if (v->rx - v->lx <= 1)
		{
			v->value = 0;
			answ = v->pos_l;
			v->pos_l = INT_MAX;
			v->pos_r = INT_MIN;
			return answ;
		}
		if (pos >= v->left->rx || pos > v->left->pos_r)
		{
			answ = set(pos, v->right);
			v->refresh();
		}
		else if (pos < v->lx)
		{
			if (v->left->value)
			{
				answ = set(pos, v->left);
				v->refresh();
			}
			else
			{
				answ = set(pos, v->right);
				v->refresh();
			}
		}
		else
		{
			answ = set(pos, v->left);
			v->refresh();
		}
		
		return answ;
	}

	int set_left(Node*& v)
	{
		if (v->rx - v->lx <= 1)
		{
			v->value = 0;
			int answ = v->pos_l;
			v->pos_l = INT_MAX;
			v->pos_r = INT_MIN;
			return answ;
		}
		int answ = INT_MAX;
		if (!v->left->value)
		{
			answ = set_left(v->right);
		}
		else
		{
			answ = set_left(v->left);
		}
		v->refresh();
		return answ;
	}

	void unset(int pos, Node*& v)
	{
		if (v->rx - v->lx <= 1)
		{
			v->value = 1;
			v->pos_l = v->pos_r = v->lx;
			return;
		}
		if (pos >= v->left->rx)
		{
			unset(pos, v->right);
		}
		else
		{
			unset(pos, v->left);
		}
		v->refresh();
	}

	

public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void build(vector<int>& arr)
	{
		build(arr, m_root);
	}

	int set(int pos)
	{
		int temp = set(pos, m_root);
		if (temp == INT_MAX)
		{
			return set_left(m_root);
		}
		else
		{
			return temp;
		}
	}

	void unset(int pos)
	{
		unset(pos, m_root);
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
	freopen("parking.in", "r", stdin);
	freopen("parking.out", "w", stdout);

	int n, m;
	cin >> n >> m;
	vector <int> park(n, 1);
	Tree tree(new Node(0, 0, n));
	tree.build(park);
	for (int i = 0; i < m; i++)
	{
		string in;
		cin >> in;
		if (in == "enter")
		{
			int pos;
			cin >> pos;
			pos--;
			int res = tree.set(pos);
			//if (res == INT_MAX) { res = 0; }
			cout << res + 1 << '\n';
		}
		else
		{
			int pos;
			cin >> pos;
			pos--;
			tree.unset(pos);
		}
	}

	return 0;
}