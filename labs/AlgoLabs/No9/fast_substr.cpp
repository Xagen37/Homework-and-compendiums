#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  string p, t;
  cin >> p >> t;
  string s = p + "#" + t;

  vector <int> z(s.length(), 0);
  int left, right;
  left = right = 0;
  for (int i = 1; i < s.length(); i++)
  {
    z[i] = max(0, min(right - i, z[i - left]));
    while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]])
    {
      z[i]++;
    }
    if (i + z[i] > right)
    {
      left = i;
      right = i + z[i];
    }
  }

  int cnt = 0;
  vector <int> ans;
  for (int i = p.length() + 1; i < s.length(); i++)
  {
    if (z[i] == p.length())
    {
      cnt++;
      ans.push_back(i - p.length());
    }
  }

  cout << cnt << '\n';
  for (int i = 0; i < ans.size(); i++)
  {
    cout << ans[i] << ' ';
  }
  return 0;
}