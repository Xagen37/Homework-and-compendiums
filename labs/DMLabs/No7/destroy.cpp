#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

struct Graph
{
  Graph(int n)
    : par(n)
    , rank(n, 1)
  {
    for (int i = 0; i < n; i++)
    {
      par[i] = i;
    }
  }

  void add_edge(int left, int right, long long weight)
  {
    edges.insert({ weight, {left, right} });
  }

  void mst()
  {
    for (auto it = edges.begin(); it != edges.end(); )
    {
      if (get(it->second.second) != get(it->second.first))
      {
        unite(it->second.first, it->second.second);
        it = edges.erase(it);
      }
      else
      {
        it++;
      }
    }
  }

  vector <pair <int, int>> may_delete(long long int s)
  {
    vector <pair <int, int>> to_return;
    long long int cnt = 0;
    for (auto it = edges.rbegin(); it != edges.rend(); it++)
    {
      if (cnt + it->first <= s) { to_return.push_back(it->second); cnt += it->first; }
      else { break; }
    }
    return to_return;
  }

private:
  int get(int v)
  {
    return (par[v] == v) ? par[v] : par[v] = get(par[v]);
  }

  void unite(int a, int b)
  {
    a = get(a); b = get(b);
    if (a == b) { return; }
    if (rank[a] == rank[b]) { rank[a]++; }
    if (rank[a] > rank[b])
    {
      par[b] = a;
    }
    else
    {
      par[a] = b;
    }
  }

  vector <int> par;
  vector <int> rank;
  set <pair <long long int, pair<int, int>>, std::greater<pair<long long int, pair<int, int>>>> edges;
};

struct hasher
{
  const int mult = 239;
  const int mod = 1e9 + 7;
  size_t operator()(const pair<int, int>& p) const
  {
    return (((p.first * mult) % mod) + p.second) % mod;
  }
};

int main()
{
  freopen("destroy.in", "r", stdin);
  freopen("destroy.out", "w", stdout);
  
  int n, m;
  long long int s;
  cin >> n >> m >> s;
  Graph g(n);
  unordered_map <pair <int, int>, int, hasher> edges;
  for (int i = 0; i < m; i++)
  {
    int l, r;
    long long int w;
    cin >> l >> r >> w;
    l--; r--;
    g.add_edge(l, r, w);
    edges[{l, r}] = edges[{r, l}] = i;
  }

  g.mst();

  auto pre_answ = g.may_delete(s);
  set <int> answ;
  for (auto it : pre_answ)
  {
    answ.insert(edges[it] + 1);
  }

  cout << answ.size() << '\n';
  for (auto it : answ)
  {
    cout << it << ' ';
  }
  return 0;
}