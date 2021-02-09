#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
  freopen("cycles.in", "r", stdin);
  freopen("cycles.out", "w", stdout);

  int n, m; cin >> n >> m;
  vector <int> weights(n);
  for (int i = 0; i < n; i++)
  {
    cin >> weights[i];
  }

  vector <pair <bool, int>> masks(1 << n, {true, 0});
  for (int i = 0; i < m; i++)
  {
    int set_n = 0;
    int pow; cin >> pow;
    for (int k = 0; k < pow; k++)
    {
      int val; cin >> val; val--;
      set_n |= (1 << val);
    }
    masks[set_n].first = false;
  }

  int max_val = 0;
  for (int i = 0; i < masks.size(); i++)
  {
    if (masks[i].first)
    {
      max_val = max(max_val, masks[i].second);
      for (int bit = 0; bit < n; bit++)
      {
        if (!(i & (1 << bit)))
        {
          if (masks[i | (1 << bit)].first)
          {
            masks[i | (1 << bit)].second = masks[i].second + weights[bit];
          }
        }
      }
    }
    else
    {
      for (int bit = 0; bit < n; bit++)
      {
        if (!(i & (1 << bit)))
        {
          masks[i | (1 << bit)] = { false, 0 };
        }
      }
    }
  }

  cout << max_val;
  return 0;
}