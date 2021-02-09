#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct hasher
{
  const int p = 31;
  const int mod = 1e9 + 7;
  size_t operator()(const set<int>& s) const
  {
    size_t h = 0;
    for (auto it : s)
    {
      h = ((h * 239) % mod + (it + 1)) % mod;
    }
    return h;
  }
};

bool check_first(const unordered_set <set <int>, hasher>& s)
{
  for (const auto& it : s)
  {
    if (it.empty()) { return true; }
  }
  return false;
}

bool check_second(const unordered_set <set <int>, hasher>& s, int pow)
{
  vector <bool> I(1 << pow, false);
  for (const auto& it : s)
  {
    int set_n = 0;
    for (auto val : it)
    {
      set_n |= (1 << val);
    }
    I[set_n] = true;
  }

  for (int it = (1 << pow) - 1; it >= 0; it--)
  {
    if (I[it])
    {
      for (int i = 0; i < pow; i++)
      {
        if (it & (1 << i) && !I[it ^ (1 << i)])
        {
          return false;
        }
      }
    }
  }
  return true;
}

struct comp
{
  bool operator()(const set<int>& left, const set<int>& right) const
  {
    return left.size() < right.size() || left.size() == right.size() && std::less<set<int>>()(left, right);
  }
};

bool check_third(const unordered_set <set <int>, hasher>& s)
{
  set <set <int>, comp> temp(s.begin(), s.end());

  for (auto it = temp.begin(); it != temp.end(); it++)
  {
    for (auto it2 = temp.begin(); it2 != temp.end(); it2++)
    {
      if (it->size() >= it2->size()) 
      { 
        continue; 
      }
      bool found = false;
      for (auto elem : *it2)
      {
        if (!it->count(elem))
        {
          auto copy = *it;
          copy.insert(elem);
          if (s.count(copy))
          {
            found = true;
            break;
          }
        }
      }
      if (!found) { return false; }
    }
  }
  return true;
}

int main()
{
  freopen("check.in", "r", stdin);
  freopen("check.out", "w", stdout);

  int n, m;
  cin >> n >> m;
  unordered_set <set <int>, hasher> s;
  for (int i = 0; i < m; i++)
  {
    int pow; cin >> pow;
    set <int> curr_set;
    for (int k = 0; k < pow; k++)
    {
      int val; cin >> val; val--;
      curr_set.insert(val);
    }
    s.insert(curr_set);
  }

  if (check_first(s) && check_second(s, n) && check_third(s))
  {
    cout << "YES";
  }
  else
  {
    cout << "NO";
  }

  return 0;
}