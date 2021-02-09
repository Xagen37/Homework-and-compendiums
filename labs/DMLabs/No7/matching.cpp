#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
  Graph(int n)
    : gr(n)
    , matching(n, -1)
  {}

  void add_edges(int from, const vector <int>& to)
  {
    gr[from].insert(gr[from].end(), to.begin(), to.end());
  }

  vector<int> kuhn(vector <pair <int, int>>& w)
  {
    sort(w.begin(), w.end(), std::greater<pair<int, int>>());
    for (int i = 0; i < gr.size(); i++)
    {
      vector <int> used(gr.size(), 0);
      dfs(w[i].second, used);
    }
    return matching;
  }

private:
  bool dfs(int v, vector <int>& used)
  {
    if (used[v]) { return false; }
    used[v] = 1;
    for (int i = 0; i < gr[v].size(); i++)
    {
      if (matching[gr[v][i]] == -1 || dfs(matching[gr[v][i]], used))
      {
        matching[gr[v][i]] = v;
        return true;
      }
    }
    return false;
  }

  vector <vector <int>> gr;
  vector <int> matching;
};

int main()
{
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);

  int n; cin >> n;
  Graph g(n);

  vector <pair <int, int>> weights(n);
  for (int i = 0; i < n; i++)
  {
    cin >> weights[i].first;
    weights[i].second = i;
  }
  for (int i = 0; i < n; i++)
  {
    int num; cin >> num;
    vector <int> verts(num);
    for (int k = 0; k < num; k++)
    {
      cin >> verts[k];
      verts[k]--;
    }
    g.add_edges(i, verts);
  }

  auto answ = g.kuhn(weights);
  for (int v = 0; v < n; v++)
  {
    bool found = false;
    for (int i = 0; i < answ.size(); i++)
    {
      if (answ[i] == v) { cout << i + 1 << ' '; found = true; break; }
    }
    if (!found) { cout << 0 << ' '; }
  }

  return 0;
}