#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector <vector <int>> matrix;
bool comp(const int& left, const int& right)
{
  return matrix[left][right];
}

void find_path(const vector <vector <int>>& matrix, vector<int>& path)
{
  path.push_back(0);
  for (int i = 1; i < matrix.size(); i++)
  {
    int k = 0;
    for (; k < path.size() && matrix[path[k]][i]; k++)
    {}

    path.insert(path.begin() + k, i);
  }
}

void find_cycle(const vector <vector <int>>& matrix, vector <int>& path, vector <int>& answ)
{
  auto path_it = path.end() - 1;
  for (; path_it != path.begin() + 1 && !matrix[*path_it][path[0]]; path_it--)
  {}
  path_it++;
  answ.insert(answ.begin(), path.begin(), path_it);
  path.erase(path.begin(), path_it);

  path_it = path.begin();
  while (path_it != path.end())
  {
    auto answ_it = answ.begin();
    while (answ_it != answ.end() && matrix[*answ_it][*path_it]) { answ_it++; }

    if (answ_it != answ.end())
    {
      path_it++;
      answ.insert(answ_it, path.begin(), path_it);
      path.erase(path.begin(), path_it);
      path_it = path.begin();
    }
    else
    {
      path_it++;
    }
  }
}

int main()
{
  int n; cin >> n;
  matrix.resize(n, vector <int>(n, 0));
  for (int i = 1; i < n; i++)
  {
    string s; cin >> s;
    for (int j = 0; j < s.length(); j++)
    {
      if (s[j] == '1')
      {
        matrix[i][j] = 1;
      }
      else
      {
        matrix[j][i] = 1;
      }
    }
  }
  if (n == 1 || n == 2) { return 0; }

  vector <int> path;
  find_path(matrix, path);

  vector <int> answ;
  find_cycle(matrix, path, answ);

  for (int i = 0; i < answ.size(); i++)
  {
    cout << answ[i] + 1 << ' ';
  }

  return 0;
}