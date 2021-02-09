#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector <vector <int>> memo;
bool comp(const int& lhs, const int& rhs)
{
  if (memo[lhs][rhs] == -1)
  {
    cout << 1 << ' ' << lhs + 1 << ' ' << rhs + 1 << endl;
    string answ; cin >> answ;
    memo[lhs][rhs] = (answ == "YES");
    memo[rhs][lhs] = !memo[lhs][rhs];
  }
  return memo[lhs][rhs];
};

bool check_path(const vector <int>& path)
{
  for (size_t i = 0; i < path.size() - 1; i++)
  {
    if (!comp(path[i], path[i + 1])) { return false; }
  }
  return true;
}

int main()
{
  int n; cin >> n;
  vector <int> lamps(n);
  for (int i = 0; i < n; i++)
  {
    lamps[i] = i;
  }

  memo.resize(n, vector <int>(n, -1));

  stable_sort(lamps.begin(), lamps.end(), comp);

  if (is_sorted(lamps.begin(), lamps.end(), comp))
  {
    cout << 0 << ' ';
    for (int i = 0; i < n; i++)
    {
      cout << lamps[i] + 1 << ' ';
    }
  }
  else
  {
    for (int i = 0; i <= n; i++)
    {
      cout << 0 << ' ';
    }
  }
  return 0;
}