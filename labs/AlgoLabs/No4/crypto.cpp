﻿#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

class Matrix
{
public:
	int a11, a12,a21, a22;

	static int mod;

	Matrix():
		a11(1),
		a12(0),
		a21(0),
		a22(1)
	{}

	Matrix(int aa11, int aa12, int aa21, int aa22):
		a11(aa11),
		a12(aa12),
		a21(aa21),
		a22(aa22)
	{}

	friend Matrix operator*(const Matrix& l, const Matrix& r);
};

Matrix operator*(const Matrix& l, const Matrix& r)
{
	return Matrix(((l.a11 * r.a11) % Matrix::mod + (l.a12 * r.a21) % Matrix::mod) % Matrix::mod, \
		((l.a11 * r.a12) % Matrix::mod + (l.a12 * r.a22) % Matrix::mod) % Matrix::mod, \
		((l.a21 * r.a11) % Matrix::mod + (l.a22 * r.a21) % Matrix::mod) % Matrix::mod, \
		((l.a21 * r.a12) % Matrix::mod + (l.a22 * r.a22) % Matrix::mod) % Matrix::mod);
}

const Matrix E = Matrix();
int Matrix::mod = 0;

class Node
{
	Node* m_left, * m_right;
	Matrix m_value;
	int m_lx, m_rx;

public:
	Node() :
		m_left(nullptr),
		m_right(nullptr),
		m_value(E),
		m_lx(0),
		m_rx(0)
	{}

	Node(Matrix value = E, int lx = 0, int rx = 0, Node * left = nullptr, Node * right = nullptr) :
		m_left(left),
		m_right(right),
		m_value(value),
		m_lx(lx),
		m_rx(rx)
	{}

	Matrix value()
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

	void set_value(Matrix value)
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
		m_value = m_left->value() * m_right->value();
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

	void build(Matrix* arr, int size, Node*& v)
	{
		if (v->r_border() - v->l_border() <= 1)
		{
			if (v->l_border() < size)
			{
				v->set_value(arr[v->l_border()]);
			}
			return;
		}

		v->set_left(new Node(E, v->l_border(), v->mid()));
		v->set_right(new Node(E, v->mid(), v->r_border()));
		Node* left = v->left();
		Node* right = v->right();
		build(arr, size, left);
		build(arr, size, right);
		v->refresh();
	}

	void set(int dest, Matrix val, Node*& v)
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

	Matrix sum(int l, int r, Node* v)
	{
		if (l >= v->r_border() || r <= v->l_border())
		{
			return E;
		}
		if (v->l_border() >= l && v->r_border() <= r)
		{
			return v->value();
		}
		Matrix sum_l = sum(l, r, v->left());
		Matrix sum_r = sum(l, r, v->right());
		return sum_l * sum_r;
	}
public:
	Tree(Node* root = nullptr) :
		m_root(root)
	{}

	void build(Matrix* arr, int size)
	{
		build(arr, size, m_root);
	}


	void set(int dest, Matrix val)
	{
		set(dest, val, m_root);
	}

	Matrix sum(int left, int right)
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
	freopen("crypto.in", "r", stdin);
	freopen("crypto.out", "w", stdout);

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int r, n, m;
	cin >> r >> n >> m;
	Matrix::mod = r;
	Matrix inp[200000];
	for (int i = 0; i < n; i++)
	{
		int a11, a12, a21, a22;
		cin >> a11 >> a12 >> a21 >> a22;
		inp[i] = Matrix(a11, a12, a21, a22);
	}
	Tree tree(new Node(E, 0, n));
	tree.build(inp, n);

	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		Matrix res = tree.sum(l - 1, r);
		cout << res.a11 << ' ' << res.a12 << '\n' << res.a21 << ' ' << res.a22 << '\n' << '\n';
	}
	return 0;
}