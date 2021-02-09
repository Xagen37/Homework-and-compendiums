#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Graph
{
  const static long long int INF = 1e18;

  Graph(long long int n)
    : gr(n)
    , dp(n, INF)
  {}

  void add_edge(long long int left, long long int right, long long int weight)
  {
    gr[left].push_back({ right, weight });
  }

  void calc(long long int start)
  {
    vector <bool> used(gr.size(), 0);
    dp[start] = 0;
    used[start] = 1;
    set <pair <long long int, long long int>> s;

    for (size_t i = 0; i < gr.size(); i++)
    {
      s.insert({ dp[i], i });
    }

    for (size_t i = 0; i < gr.size(); i++)
    {
      long long int v = -1;
      long long int min_d = INF;
      if (!s.empty())
      {
        v = s.begin()->second;
        min_d = s.begin()->first;
        s.erase(s.begin());
      }
      if (min_d == INF) { break; }

      used[v] = 1;
      for (auto u : gr[v])
      {
        if (!used[u.first])
        {
          if (dp[u.first] > dp[v] + u.second)
          {
            s.erase(s.find({ dp[u.first], u.first }));
            dp[u.first] = dp[v] + u.second;
            s.insert({ dp[u.first], u.first });
          }
        }
      }
    }
  }

  vector <long long int> get_dist()
  {
    return dp;
  }

  void flush()
  {
    dp.assign(dp.size(), INF);
  }

private:
  vector <vector <pair <long long int, long long int>>> gr;
  vector <long long int> dp;
};

int main()
{
  long long int n, m;
  cin >> n >> m;
  Graph g(n);

  for (long long int i = 0; i < m; i++)
  {
    long long int l, r, w;
    cin >> l >> r >> w;
    l--; r--;
    g.add_edge(l, r, w);
    g.add_edge(r, l, w);
  }
  long long int a, b, c;
  cin >> a >> b >> c;
  a--; b--; c--;
  g.calc(a);
  auto dist_from_a = g.get_dist();
  g.flush();
  long long int ab = dist_from_a[b];
  long long int ac = dist_from_a[c];
  if (ab == ac && ab == Graph::INF)
  {
    cout << -1;
  }
  else
  {
    g.calc(b);
    auto dist_from_b = g.get_dist();
    long long int bc = dist_from_b[c];
    long long int answ1 = min(min(ab + bc, ac + bc), min(2 * ab + ac, 2 * ac + ab));
    long long int answ2 = min(min(ab + ac, 2 * ab + bc), min(2 * bc + ab, 2 * ac + bc));
    long long int answ = min(2 * bc + ac, min(answ1, answ2));
    if (answ >= Graph::INF)
    {
      cout << -1;
    }
    else
    {
      cout << answ;
    }
  }

  return 0;
}