#include <iostream>
#include <string>
#include <vector>

using namespace std;

const unsigned long long int P = 31;
const unsigned int long long MOD = 1e9 + 7;
vector <unsigned long long int> h;
vector <unsigned long long int> Ps;
unsigned long long int get_hash(int l, int r)
{
  return (h[r + 1] - (h[l] * Ps[r - l + 1]) % MOD + MOD) % MOD;
}

int main()
{  
  string s; cin >> s;
  int m; cin >> m;
  h.resize(s.length() + 1, 0);
  Ps.resize(1e5 + 1, 1);
  for (unsigned int i = 0; i < s.length(); i++)
  {
    h[i + 1] = ((h[i] * P) % MOD + s[i]) % MOD;
    Ps[i + 1] = (Ps[i] * P) % MOD;
  }

  for (int i = 0; i < m; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--; b--; c--; d--;
    if (b - a != d - c) 
    {
      cout << "No\n";
      continue;
    }
    unsigned long long int h1 = get_hash(a, b);
    unsigned long long int h2 = get_hash(c, d);

    if (h1 == h2) { cout << "Yes\n"; }
    else { cout << "No\n"; }
  }
  return 0;
}