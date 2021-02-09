#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Graph
{
  struct comp
  {
    bool operator() (const pair<int, int>& lhs, const pair <int, int>& rhs) const
    {
      return (lhs.second < rhs.second ||
        lhs.second == rhs.second && lhs.first < rhs.first);
    }
  };

  Graph(int n)
    : gr(n)
    , vert()
  {}

  void add_edge(int left, int right)
  {
    gr[left].insert(right);
    gr[right].insert(left);
  }

  void pryufer(vector <int>& answ)
  {
    answ.clear();
    for (int i = 0; i < gr.size(); i++)
    {
      vert.insert({ i, gr[i].size() });
    }

    for (int i = 0; i < gr.size() - 2; i++)
    {
      auto it = vert.begin();
      int v = it->first;
      vert.erase(vert.begin());
      for (int u : gr[v])
      {
        answ.push_back(u);
        auto copy_it = vert.find({u, gr[u].size()});
        vert.erase(copy_it);
        gr[u].erase(v);
        vert.insert({ u, gr[u].size() });
      }
    }
  }

private:
  vector <set <int>> gr;
  set <pair <int, int>, comp> vert;
};

int main()
{
  int n; cin >> n;
  Graph g(n);
  for (int i = 0; i < n - 1; i++)
  {
    int left, right;
    cin >> left >> right;
    left--; right--;
    g.add_edge(left, right);
  }

  vector <int> answ;
  g.pryufer(answ);
  for (int i = 0; i < answ.size(); i++)
  {
    cout << answ[i] + 1 << ' ';
  }
  return 0;
}