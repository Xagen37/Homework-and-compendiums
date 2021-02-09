#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
  string s;
  cin >> s;
  vector <int> pref(s.length(), 0);
  for (int i = 1; i < s.length(); i++)
  {
    int k = pref[i - 1];
    while (k > 0 && s[i] != s[k]) { k = pref[k - 1]; }
    if (s[i] == s[k]) { k++; }
    pref[i] = k;
  }

  for (int i = 0; i < pref.size(); i++)
  {
    cout << pref[i] << ' ';
  }
  return 0;
}