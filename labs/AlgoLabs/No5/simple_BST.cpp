#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node
{
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node * parent = nullptr;
};

Node* parent = nullptr;

Node * exists(Node * node, int x)
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

void insert(Node* node, int x)
{
	if (node->value == x) { return; }
	if (x < node->value)
	{
		if (node->left == nullptr)
		{
			node->left = new Node;
			node->left->value = x;
			node->left->parent = node;
		}
		else
		{
			insert(node->left, x);
		}
	}
	else
	{
		if (node->right == nullptr)
		{
			node->right = new Node;
			node->right->value = x;
			node->right->parent = node;
		}
		else
		{
			insert(node->right, x);
		}
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

void remove(int x)
{
	Node* node = exists(parent, x);
	if (node == nullptr) { return; }
	Node* p = node->parent;
	if (node->left == nullptr && node->right == nullptr)
	{
		if (p == nullptr) { parent = nullptr; return; }
		if (p->left == node) { p->left = nullptr; }
		else { p->right = nullptr; }
	}
	else if (node->left == nullptr || node->right == nullptr)
	{
		if (!node->left)
		{
			if (p == nullptr) 
			{
				parent = node->right;
			}
			else if (p->left == node)
			{
				p->left = node->right;
			}
			else
			{
				p->right = node->right;
			}
			node->right->parent = p;
		}
		else
		{
			if (p == nullptr)
			{
				parent = node->left;
			}
			else if (p->left == node)
			{
				p->left = node->left;
			}
			else
			{
				p->right = node->left;
			}
			node->left->parent = p;
		}
	}
	else
	{
		Node* s = next(x);
		node->value = s->value;
		if (s->parent->left == s)
		{
			s->parent->left = s->right;
			if (s->right != nullptr)
			{
				s->right->parent = s->parent;
			}
		}
		else
		{
			s->parent->right = s->left;
			if (s->left != nullptr)
			{
				s->right->parent = s->parent;
			}
		}
	}
}



int main()
{
	string in;
	while (cin >> in)
	{
		int x;
		cin >> x;
		if (in == "insert")
		{
			if (parent == nullptr)
			{
				parent = new Node;
				parent->value = x;
			}
			else
			{
				insert(parent, x);
			}
		}
		else if (in == "delete")
		{
			if (parent != nullptr)
			{
				remove(x);
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

	return 0;
}
