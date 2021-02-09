#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph
{
  static const int NO_EDGE = 100000;
  static const long long int INF = 1e18;
  Graph(int n)
    : gr(n, vector <int>(n))
    , dp(n, INF)
  {}

  void add_edge(int from, int to, int weight)
  {
    gr[from][to] = weight;
  }

  void calc()
  {
    dp[0] = 0;
    vector <int> p(gr.size(), -1);
    int cnt = 0;
    int last_relax = 0;
    while (true)
    {
      bool flag = true;
      for (int v = 0; v < gr.size(); v++)
      {
        for (int u = 0; u < gr.size(); u++)
        {
          if (gr[u][v] != NO_EDGE)
          {
            if (dp[v] > dp[u] + gr[u][v])
            {
              dp[v] = dp[u] + gr[u][v];
              p[v] = u;
              last_relax = v;
              flag = false;
            }
          }
        }
      }
      cnt++;
      if (flag) { break; }
      if (cnt >= gr.size()) { is_cycle = true; break; }
    }

    if (is_cycle)
    {
      for (int i = 0; i < gr.size(); i++)
      {
        last_relax = p[last_relax];
      }
      int u = last_relax;
      while (u != p[last_relax])
      {
        answ.push_back(last_relax);
        last_relax = p[last_relax];
      }
      answ.push_back(last_relax);
      reverse(answ.begin(), answ.end());
    }
  }

  explicit operator bool()
  {
    return is_cycle;
  }

  void print_cycle()
  {
    cout << answ.size() << '\n';
    for (int i = 0; i < answ.size(); i++)
    {
      cout << answ[i] + 1 << ' ';
    }
  }

private:
  vector <vector <int>> gr; //matrix
  vector <long long int> dp;
  bool is_cycle = false;
  vector <int> answ;
};

int main()
{
  int n;
  cin >> n;
  Graph g(n);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int w; cin >> w;
      g.add_edge(i, j, w);
    }
  }
  g.calc();

  if (g)
  {
    cout << "YES\n";
    g.print_cycle();
  }
  else
  {
    cout << "NO";
  }
  return 0;
}