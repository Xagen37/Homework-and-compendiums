#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct Graph
{
  static const long long int INF = 1e18;
  Graph(int n)
    : gr(n)
    , dp(n + 2, vector <long long int>(n, INF))
    , used_type(n, 0)
  {}

  void add_edge(int from, int to, long long int weight)
  {
    gr[from].push_back({ to, weight });
  }

  void calc(int start)
  {
    dp[0][start] = 0;

    int n = dp.size() - 2;
    for (int i = 1; i <= n; i++)
    {
      for (int v = 0; v < gr.size(); v++)
      {
        if (dp[i - 1][v] != INF)
        {
          for (auto u : gr[v])
          {
            dp[i][u.first] = min(dp[i][u.first], dp[i - 1][v] + u.second);
          }
          dp[i][v] = min(dp[i][v], dp[i - 1][v]);
        }
      }
    }

    dp[n + 1] = dp[n];
    vector <bool> marked(gr.size(), 0);
    bool flag = false;
    for (int v = 0; v < gr.size(); v++)
    {
      if (dp[n][v] != INF)
      {
        for (auto u : gr[v])
        {
          if (dp[n + 1][u.first] > dp[n][v] + u.second || marked[v])
          {
            dp[n + 1][u.first] = dp[n][v] + u.second;
            flag = marked[u.first] = true;
          }
        }
        dp[n + 1][v] = min(dp[n + 1][v], dp[n][v]);
      }
    }

    if (flag)
    {
      vector <int> used(gr.size(), 0);
      function<void(int)> dfs = [&](int v)
      {
        used[v] = 1;
        marked[v] = 1;
        for (auto u : gr[v])
        {
          if (!used[u.first])
          {
            dfs(u.first);
          }
        }
      };
      for (int i = 0; i < marked.size(); i++)
      {
        if (marked[i])
        {
          dfs(i);
        }
      }
    }

    for (int i = 0; i < gr.size(); i++)
    {
      if (marked[i]) { used_type[i] = -1; }
      else if (dp[dp.size() - 1][i] == INF) { used_type[i] = 0; }
      else
      {
        used_type[i] = 1;
      }
    }
  }

  vector <long long int>& get_dist()
  {
    return dp[dp.size() - 1];
  }

  vector <int>& get_types()
  {
    return used_type;
  }

private:
  vector <vector <pair <int, long long int>>> gr;
  vector <vector <long long int>> dp; //[turn][vertex]
  vector <int> used_type; // 0 - not used, 1 - used, -1 - used twice with negative cycle
};

int main()
{
  int n, m, s;
  cin >> n >> m >> s; s--;
  Graph g(n);

  for (int i = 0; i < m; i++)
  {
    long long int l, r, weight;
    cin >> l >> r >> weight;
    l--; r--;
    g.add_edge(l, r, weight);
  }
  g.calc(s);

  const auto& dist = g.get_dist();
  const auto& types = g.get_types();

  for (int i = 0; i < n; i++)
  {
    if (!types[i]) { cout << "*\n"; }
    else if (types[i] == -1) { cout << "-\n"; }
    else
    {
      cout << dist[i] << '\n';
    }
  }

  return 0;
}