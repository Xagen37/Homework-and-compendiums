#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph
{
  static const long long int INF = 1e18;
  Graph(int n, int k)
    : gr(n)
    , dp(k + 1, vector <long long int> (n, INF))
  {}

  void add_edge(int from, int to, int weight)
  {
    gr[from].push_back({ to, weight });
  }

  void calc(int k, int start)
  {
    dp[0][start] = 0;

    for (int i = 1; i <= k; i++) //turns
    {
      for (int v = 0; v < gr.size(); v++) //vertexes
      {
        for (auto u : gr[v])
        {
          if (dp[i - 1][v] != INF)
          {
            dp[i][u.first] = min(dp[i][u.first], dp[i - 1][v] + u.second);
          }
        }
      }
    }
  }

  vector <vector <long long int>>& get_dist()
  {
    return dp;
  }

private:
  vector <vector <pair <int, int>>> gr; 
  vector <vector <long long int>> dp; //[turn][vertex]
};

int main()
{
  int n, m, k, s;
  cin >> n >> m >> k >> s; s--;
  Graph g(n, k);

  for (int i = 0; i < m; i++)
  {
    int l, r, w;
    cin >> l >> r >> w;
    l--; r--;
    g.add_edge(l, r, w);
  }

  g.calc(k, s);
  const auto& dist = g.get_dist();

  for (int i = 0; i < n; i++)
  {
    if (dist[k][i] == Graph::INF)
    {
      cout << -1 << '\n';
    }
    else
    {
      cout << dist[k][i] << '\n';
    }
  }

  return 0;
}