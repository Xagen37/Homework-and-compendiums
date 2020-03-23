﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Node
{
public:
	Node* left, * right;
	int value, coordinate;
	int lx, rx;
	int add;

	Node() :
		left(nullptr),
		right(nullptr),
		value(INT_MIN),
		coordinate(0),
		lx(0),
		rx(0),
		add(0)
	{}

	Node(int ivalue = 0, int ilx = 0, int irx = 0, Node * ileft = nullptr, Node * iright = nullptr) :
		left(ileft),
		right(iright),
		value(ivalue),
		coordinate(0),
		lx(ilx),
		rx(irx),
		add(0)
	{}

	int mid()
	{
		return lx + (rx - lx) / 2;
	}

	void refresh()
	{
		if (left->value > right->value)
		{
			value = left->value;
			coordinate = left->coordinate;
		}
		else
		{
			value = right->value;
			coordinate = right->coordinate;
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
			if (v->lx >= arr.size())
			{
				v->value = -600000;
				v->coordinate = -1;
			}
			else
			{
				v->value = arr[v->lx];
				v->coordinate = v->lx;
			}
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
		v->left->add += v->add;
		v->left->value += v->add;
		v->right->add += v->add;
		v->right->value += v->add;
		v->add = 0;
		v->refresh();
	}

	void add(int val, int left, int right, Node*& v)
	{
		propagate(v);
		if (left >= v->rx || v->lx >= right) { return; }
		if (v->lx >= left && v->rx <= right) 
		{
			v->add += val;
			v->value += val;
			return;
		}
		add(val, left, right, v->left);
		add(val, left, right, v->right);
		v->refresh();
	}

	pair<int, int> quest(int left, int right, Node*& v)
	{
		propagate(v);
		if (left >= v->rx || v->lx >= right) { return {INT_MIN, -1}; }
		if (v->lx >= left && v->rx <= right)
		{
			return { v->value, v->coordinate };
		}
		auto s1 = quest(left, right, v->left);
		auto s2 = quest(left, right, v->right);
		if (s1.first > s2.first)
		{
			return s1;
		}
		else
		{
			return s2;
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

	void add(int val, int left, int right)
	{
		add(val, left, right, m_root);
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

bool comp_less(const pair<pair<int, int>, bool>& left, const pair<pair<int, int>, bool>& right)
{
	return left.second;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	const int SHIFT = 524288;
	const int SHAFT = 262144;

	int n;
	cin >> n;
	vector <vector <pair<pair <int, int>, bool>>> queries(SHIFT, vector <pair <pair<int, int>, bool>>());
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1 += SHAFT;
		y1 += SHAFT;
		x2 += SHAFT;
		y2 += SHAFT;
		queries[x1].push_back({ { y1, y2 }, true });
		queries[x2].push_back({ { y1, y2 }, false });
	}
	Tree tree(new Node(0, 0, SHIFT));
	vector <int> line(SHIFT, 0);
	tree.build(line);
	auto t = tree.quest(0, line.size());
	int max_n = t.first, max_x = 0, max_y = t.second;
	for (int i = 0; i < queries.size(); i++)
	{
		if (queries[i].empty()) { continue; }
		sort(queries[i].begin(), queries[i].end(), comp_less);
		for (int k = 0; k < queries[i].size(); k++)
		{
			if (queries[i][k].second)
			{
				tree.add(1, queries[i][k].first.first, queries[i][k].first.second + 1);
			}
			else
			{
				tree.add(-1, queries[i][k].first.first, queries[i][k].first.second + 1);
			}

			t = tree.quest(0, line.size());
			if (t.first > max_n)
			{
				max_n = t.first;
				max_x = i;
				max_y = t.second;
			}
		}
	}

	cout << max_n << '\n';
	cout << max_x - SHAFT << ' ' << max_y - SHAFT;

	return 0;
}