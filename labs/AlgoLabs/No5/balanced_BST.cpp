#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <string>
#include <ctime>

using namespace std;

struct Node
{
	int value, y;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

Node* parent = nullptr;

pair<Node*, Node*> split(Node* tree, int x)
{
	if (tree == nullptr) { return { nullptr, nullptr }; }
	if (x < tree->value)
	{
		auto p = split(tree->left, x);
		tree->left = p.second;
		return { p.first, tree };
	}
	else
	{
		auto p = split(tree->right, x);
		tree->right = p.first;
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
		return a;
	}
	else
	{
		b->left = merge(a, b->left);
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
		return node;
	}
	else
	{
		if (node->value < a->value)
		{
			a->left = insert(a->left, node);
		}
		else if (node->value > a->value)
		{
			a->right = insert(a->right, node);
		}
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
		}
		else
		{
			erase(a->left, x);
		}
	}
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


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(0));

	string in;
	while (cin >> in)
	{
		int x;
		cin >> x;
		if (in == "insert")
		{
			if (exists(parent, x) == nullptr)
			{
				int y;
				y = rand();
				Node* n = new Node;
				n->value = x;
				n->y = y;
				parent = insert(parent, n);
			}
		}
		else if (in == "delete")
		{
			if (exists(parent, x) != nullptr) 
			{
				erase(parent, x);
			}
		}
		else if (in == "exists")
		{
			if (exists(parent, x) == nullptr)
			{
				cout << "false\n";
			}
			else
			{
				cout << "true\n";
			}
		}
		else if (in == "next")
		{
			if (parent == nullptr) { cout << "none\n"; }
			else
			{
				Node* answ = next(x);
				if (answ == nullptr) { cout << "none\n"; }
				else { cout << answ->value << '\n'; }
			}
		}
		else if (in == "prev")
		{
			if (parent == nullptr) { cout << "none\n"; }
			else
			{
				Node* answ = prev(x);
				if (answ == nullptr) { cout << "none\n"; }
				else { cout << answ->value << '\n'; }
			}
		}
	}
}
