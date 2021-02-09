#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct cmp
{
  bool operator()(const pair<long long int, long long int>& left, const pair<long long int, long long int>& right) const
  {
    return left.first < right.first || left.first == right.first && left.second > right.second;
  }
};

struct cmp2
{
  bool operator()(const pair<long long int, long long int>& left, const pair<long long int, long long int>& right) const
  {
    return left.second < right.second;
  }
};

int main()
{
  freopen("schedule.in", "r", stdin);
  freopen("schedule.out", "w", stdout);

  size_t n; cin >> n;
  vector <pair <long long int, long long int>> inp(n);
  for (size_t i = 0; i < n; i++)
  {
    cin >> inp[i].first >> inp[i].second;
  }
  sort(inp.begin(), inp.end(), cmp());

  long long int cnt = 0;
  multiset <long long int> curr;
  for (size_t i = 0; i < n; i++)
  {
    if (inp[i].first > curr.size())
    {
      curr.insert(inp[i].second);
    }
    else
    {
      if (!curr.empty() && *curr.begin() < inp[i].second)
      {
        cnt += *curr.begin();
        curr.erase(curr.begin());
        curr.insert(inp[i].second);
      }
      else
      {
        cnt += inp[i].second;
      }
    }
  }

  cout << cnt;
  return 0;
}