#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Graph
{
  Graph(int n)
    : gr(n)
    , dp(n, INF)
  {}

  void add_edge(int left, int right, int weight)
  {
    gr[left].push_back({ right, weight });
  }

  void calc()
  {
    vector <bool> used (gr.size(), 0);
    dp[0] = 0;
    used[0] = 1;
    set <pair <long long int, int>> s;

    for (size_t i = 0; i < gr.size(); i++)
    {
      s.insert({ dp[i], i });
    }

    for (size_t i = 0; i < gr.size(); i++)
    {
      int v = -1;
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

  vector <long long int>& get_dist()
  {
    return dp;
  }

private:
  long long int INF = 30000000000;
  vector <vector <pair <int, int>>> gr;
  vector <long long int> dp;
};

int main()
{
  int n, m;
  cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; i++)
  {
    int l, r, w;
    cin >> l >> r >> w;
    l--; r--;
    g.add_edge(l, r, w);
    g.add_edge(r, l, w);
  }

  g.calc();
  const auto& dist = g.get_dist();
  for (size_t i = 0; i < dist.size(); i++)
  {
    cout << dist[i] << ' ';
  }

  return 0;
}