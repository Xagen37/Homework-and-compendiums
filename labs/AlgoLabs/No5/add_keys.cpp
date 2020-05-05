#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector <int> used;
int used_cnt;

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
			v->value = 1;
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

	void unset(int pos, Node*& v)
	{
		if (v->rx - v->lx <= 1)
		{
			v->value = 0;
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
			return 200000;
		}
		else
		{
			return temp;
		}
		//return temp;
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

Tree * tree;

struct Dec
{
	int priority = 1, value = 0, cnt = 1;
	Dec* left = nullptr;
	Dec* right = nullptr;
};

int cnt(Dec* it)
{
	return it ? it->cnt : 0;
}

void upd_cnt(Dec* it)
{
	if (it)
	{
		it->cnt = cnt(it->left) + cnt(it->right) + 1;
	}
}

Dec* merge(Dec* t1, Dec* t2)
{
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


pair<Dec*, Dec*> split(Dec* t, int k)
{
	if (t == nullptr)
	{
		return { nullptr, nullptr };
	}
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

void insert(Dec*& t, int pos, int val)
{
	Dec* l, * r;
	auto p = split(t, pos);
	Dec* n = new Dec;
	n->value = val;
	n->priority = rand();
	p.first = merge(p.first, n);
	t = merge(p.first, p.second);
}

void set(Dec*& t, int pos, int val)
{
	auto p = split(t, pos);
	Dec* l = p.first;
	auto p2 = split(p.second, 1);
	Dec* m = p2.first;
	Dec* r = p2.second;
	if (m->value == 0)
	{
		m->value = val;
		if (used[pos]) { used_cnt--; }
		used[pos] = false;
		tree->set(pos);
		l = merge(l, m);
		t = merge(l, r);
		return;
	}
	r = merge(m, r);

	if (used_cnt > 0)
	{
		int place = tree->set(pos);
		if (place < used.size())
		{
			used[place] = false;
			used_cnt--;
			auto move = split(r, place - pos);
			auto move2 = split(move.second, 1);
			r = merge(move.first, move2.second);
		}
	}
	Dec* n = new Dec;
	n->value = val;
	n->priority = rand();
	l = merge(l, n);
	t = merge(l, r);
}

Dec* parent = nullptr;
Dec* build(int n, int y = 131072)
{
	if (n <= 0) { return nullptr; }
	if (n == 1)
	{
		Dec* t = new Dec();
		t->value = 0;
		t->priority = 1;
		return t;
	}
	Dec* t = new Dec();
	t->value = 0;
	t->priority = y;
	n--;
	int l = n >> 1;
	int r = n - l;
	t->left = build(l, y >> 1);
	t->right = build(r, y >> 1);
	upd_cnt(t);
	return t;
}

void output(Dec* t, vector <int>& answ) {
	if (!t) { return; }
	output(t->left, answ);
	answ.push_back(t->value);
	output(t->right, answ);
}

void output(Dec* t) {
	if (!t)  return;
	output(t->left);
	cout << t->value << ' ';
	output(t->right);
}



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	used.resize(m, 1);
	used_cnt = m;
	parent = build(m);
	tree = new Tree(new Node(0, 0, m));
	tree->build(used);
	for (int i = 1; i <= n; i++)
	{
		int L;
		cin >> L;
		set(parent, L - 1, i);
	}
	vector <int> answ;
	output(parent, answ);

	int end = answ.size() - 1;
	while (!answ[end]) { end--; }
	cout << end + 1 << '\n';
	for (int i = 0; i <= end; i++)
	{
		cout << answ[i] << ' ';
	}
	return 0;
}