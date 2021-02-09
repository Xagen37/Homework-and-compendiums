#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Graph
{
  Graph(int n)
    : gr(n)
    , colour(n, -1)
    , banned_colours(n)
  {}

  void add_edge(int left, int right)
  {
    gr[left].push_back(right);
    gr[right].push_back(left);
  }

  int find_mex(const set<int>& banned)
  {
    if (banned.empty()) { return 0; }
    auto it = banned.begin();
    for (int i = 0; it != banned.end(); i++, it++)
    {
      if (i != *it)
      {
        return i;
      }
    }
    return *(--banned.end()) + 1;
  }

  void colour_bfs()
  {
    vector <int> added(gr.size(), 0);
    queue <int> q;
    q.push(0);
    added[0] = 1;
    while (!q.empty())
    {
      int curr = q.front(); q.pop();
      colour[curr] = find_mex(banned_colours[curr]);
      for (int u : gr[curr])
      {
        if (colour[u] == -1)
        {
          banned_colours[u].insert(colour[curr]);
          if (!added[u]) { q.push(u); added[u] = 1; }
        }
      }
    }
  }

  int max_odd_k()
  {
    size_t k = 0;
    for (int i = 0; i < gr.size(); i++)
    {
      k = max(k, gr[i].size());
    }
    return (k % 2) ? k : k + 1;
  }

  vector <int>& get_colours()
  {
    return colour;
  }
private:
  vector <vector <int>> gr;
  vector <int> colour;
  vector <set <int>> banned_colours;
};

int main()
{
  int n, m; cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; i++)
  {
    int l, r;
    cin >> l >> r;
    l--; r--;
    g.add_edge(l, r);
  }

  g.colour_bfs();
  cout << g.max_odd_k() << '\n';
  const auto& answ = g.get_colours();
  for (auto it : answ)
  {
    cout << it + 1 << '\n';
  }

  return 0;
}