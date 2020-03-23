﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Node
{
public:
	Node* left, * right;
	int length;
	bool left_border, right_border; //1 = W, 0 = B
	int sections;
	int lx, rx;
	int set;

	Node() :
		left(nullptr),
		right(nullptr),
		length(0),
		left_border(1),
		right_border(1),
		sections(0),
		lx(0),
		rx(0),
		set(2)
	{}

	Node(int ilength = 0, int ilx = 0, int irx = 0, Node * ileft = nullptr, Node * iright = nullptr) :
		left(ileft),
		right(iright),
		length(ilength),
		left_border(1),
		right_border(1),
		sections(0),
		lx(ilx),
		rx(irx),
		set(2)
	{}

	int mid()
	{
		return lx + (rx - lx) / 2;
	}

	void refresh()
	{
		length = left->length + right->length;
		sections = left->sections + right->sections;
		if (!left->right_border && !right->left_border)
		{
			sections--;
		}
		left_border = left->left_border;
		right_border = right->right_border;
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

	void build(vector <bool>& arr, Node*& v)
	{
		if (v->rx - v->lx <= 1)
		{
			return;
		}

		v->left = new Node(0, v->lx, v->mid());
		v->right = new Node(0, v->mid(), v->rx);
		Node* left = v->left;
		Node* right = v->right;
		build(arr, left);
		build(arr, right);
		v->refresh();
	}

	void propagate(Node*& v)
	{
		if (v->rx - v->lx <= 1) { return; }
		if (v->set == 2) { return; }
		v->left->set = v->set;
		v->right->set = v->set;
		v->left->left_border = v->left->right_border = v->set;
		v->right->left_border = v->right->right_border = v->set;
		if (v->set)
		{
			v->left->sections = v->left->length = 0;
			v->right->sections = v->right->length = 0;
		}
		else
		{
			v->left->sections = v->right->sections = 1;
			v->left->length = v->left->rx - v->left->lx;
			v->right->length = v->right->rx - v->right->lx;
		}
		v->set = 2;
		v->refresh();
	}

	void set(bool color, int left, int right, Node*& v)
	{
		propagate(v);
		if (v->lx >= right || v->rx <= left) { return; }
		if (v->lx >= left && v->rx <= right)
		{
			v->set = color;
			v->left_border = v->right_border = color;
			if (color)
			{
				v->length = 0;
				v->sections = 0;
			}
			else
			{
				v->length = v->rx - v->lx;
				v->sections = 1;
			}
			return;
		}
		set(color, left, right, v->left);
		set(color, left, right, v->right);
		v->refresh();
	}

public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void build(vector<bool>& arr)
	{
		build(arr, m_root);
	}

	pair<int, int> set(bool color, int left, int right)
	{
		set(color, left, right, m_root);
		return { m_root->sections, m_root->length };
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
	vector <bool> a(1000100, true);
	Tree tree(new Node(0, 0, 1000100));
	tree.build(a);
	for (int i = 0; i < n; i++)
	{
		char c;
		int l, d;
		cin >> c >> l >> d;
		l += 500010;
		pair <int, int> ans;
		if (c == 'W')
		{
			ans = tree.set(1, l, l + d);
		}
		else
		{
			ans = tree.set(0, l, l + d);
		}
		cout << ans.first << ' ' << ans.second << '\n';
	}
	return 0;
}