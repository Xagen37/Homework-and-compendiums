#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <int> queue;
	int queue_pt = 0;
	for (int i = 0; i < n; i++)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			int val;
			cin >> val;
			queue.push_back(val);
			break;
		}
		case 2:
		{
			queue_pt++;
			break;
		}
		case 3:
		{
			queue.pop_back();
			break;
		}
		case 4:
		{
			int val;
			cin >> val;
			for (int i = queue_pt; i < queue.size(); i++)
			{
				if (queue[i] == val)
				{
					cout << i - queue_pt << '\n';
					break;
				}
			}
			break;
		}
		case 5:
		{
			cout << queue[queue_pt] << '\n';
			break;
		}
		default:
			break;
		}
	}

	return 0;
}