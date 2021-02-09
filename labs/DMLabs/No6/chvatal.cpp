#include <algorithm>
#include <deque>
#include <random>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool check_cycle(const deque<int>& q, const vector <vector<int>>& matrix)
{
  for (int i = 0; i < q.size() - 1; i++)
  {
   if (!matrix[q[i]][q[i + 1]]) { return false; } 
  }
  if (!matrix[q[q.size() - 1]][q[0]]) { return false; }
  return true;
}

int main()
{
  int n; cin >> n;
  vector <vector <int>> matrix(n, vector <int>(n, 0));
  for (int i = 1; i < n; i++)
  {
    string s; cin >> s;
    for (int j = 0; j < s.length(); j++)
    {
      matrix[i][j] = matrix[j][i] = (s[j] == '1') ? 1 : 0;
    }
  }

  deque<int> q;
  std::random_device rd;
  std::mt19937 g(rd());
  while(true)
  {
    q.clear();
    for (int i = 0; i < n; i++) 
    { 
      q.push_back(i); 
    }
    shuffle(q.begin(), q.end(), g);

    int iter = n * (n - 1);
    for (int i = 0; i < iter; i++)
    {
      if (!matrix[q[0]][q[1]])
      {
        int k = 2;
        while (!matrix[q[0]][q[k]] || (k + 1 < n && !matrix[q[1]][q[k + 1]]))
        {
          k++;
        }
        reverse(q.begin() + 1, q.begin() + k + 1);
      }
      q.push_back(q.front());
      q.pop_front();
    }

    if (check_cycle(q, matrix)) { break; };
  }
  for (auto it = q.begin(); it != q.end(); it++)
  {
    cout << *it + 1 << ' ';
  }
  return 0;
}