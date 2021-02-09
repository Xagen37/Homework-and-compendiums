#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  string s;
  cin >> s;

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

  for (int i = 1; i < z.size(); i++)
  {
    cout << z[i] << ' ';
  }
  return 0;
}