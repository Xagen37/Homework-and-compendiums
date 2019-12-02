#include <iostream>
//#include <vector>

using namespace std;

struct Node
{
public:
	int m_val;
	Node* m_prev;
	Node* m_next;

	Node(int val, Node* prev, Node* next):
		m_val(val),
		m_prev(prev),
		m_next(next)
	{}

	Node()
	{
		m_val = 0;
		m_prev = m_next = nullptr;
	}
};

struct My_deque
{
private:
	Node* first;
	Node* last;
	int m_size;
public: 
	My_deque()
	{
		m_size = 0;
		first = last = nullptr;
	}

	int size()
	{
		return m_size;
	}
	void push_back(int val)
	{
		if (last != nullptr)
		{
			Node* to_add = new Node(val, last, nullptr);

			last->m_next = to_add;
			last = to_add;
		}
		else
		{
			Node* to_add = new Node(val, nullptr, nullptr);
			last = first = to_add;
		}
		m_size++;
	}

	int pop_back()
	{
		m_size--;
		if (last->m_prev != nullptr)
		{
			int to_return = last->m_val;
			last = last->m_prev;
			delete last->m_next;
			last->m_next = nullptr;
			return to_return;
		}
		else
		{
			int to_return = last->m_val;
			delete last;
			first = last = nullptr;
			return to_return;
		}
	}

	void push_front(int val)
	{
		if (first != nullptr)
		{
			Node* to_add = new Node(val, nullptr, first);
			first->m_prev = to_add;
			first = to_add;
		}
		else
		{
			Node* to_add = new Node(val, nullptr, nullptr);
			first = last = to_add;
		}
		m_size++;
	}

	int pop_front()
	{
		m_size--;
		if (first->m_next != nullptr)
		{
			int to_return = first->m_val;
			first = first->m_next;
			delete first->m_prev;
			first->m_prev = nullptr;
			return to_return;
		}
		else
		{
			int to_return = first->m_val;
			delete first;
			first = last = nullptr;
			return to_return;
		}
	}
};

int main()
{
	int n;
	cin >> n;
	My_deque left;
	My_deque right;
	for (int i = 0; i < n; i++)
	{
		char op;
		cin >> op;
		switch (op)
		{
		case '+':
		{
			while (left.size() < right.size())
			{
				left.push_back(right.pop_front());
			}
			int val;
			cin >> val;
			right.push_back(val);
			break;
		}
		case '-':
		{
			while (left.size() < right.size())
			{
				left.push_back(right.pop_front());
			}
			cout << left.pop_front() << '\n';
			break;
		}
		case '*':
		{
			while (left.size() < right.size())
			{
				left.push_back(right.pop_front());
			}
			int val;
			cin >> val;
			right.push_front(val);
			break;
		}
		default:
			break;
		}
	}

	return 0;
}