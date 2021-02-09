#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

struct Graph_grundy
{
  Graph_grundy(size_t n)
    : gr(n)
    , pos_type(n, 0)
    , to_cut({-1, -1})
  {}

  void add_edge(size_t from, size_t to)
  {
    gr[from].push_back(to);
  }

  int get_pos_type(size_t pos)
  {
    return pos_type[pos];
  }

  void dfs_calc(int root)
  {
    vector <int> used(gr.size(), 0);

    function<void(int)> dfs = [&](int v)
    {
      used[v] = true;
      for (auto u : gr[v])
      {
        if (!used[u])
        {
          dfs(u);
          pos_type[v] ^= (pos_type[u] + 1);
        }
      }
    };
    dfs(root);

    if (pos_type[root])
    {
      used.assign(gr.size(), 0);
      bool flag = false;
      function <void(int, int)> cut = [&](int v, int number)
      {
        used[v] = true;
        for (auto u : gr[v])
        {
          if (!used[u])
          {
            int curr = pos_type[v] ^ (pos_type[u] + 1) ^ number;
            if (!curr)
            {
              to_cut = make_pair(v, u);
              flag = true;
              return;
            }
            cut(u, curr - 1);
            if (flag) { return; }
          }
        }
      };

      cut(root, 0);
    }
  }

  pair <int, int> get_to_cut()
  {
    if (to_cut.first == -1)
    {
      throw to_cut;
    }
    return to_cut;
  }

private:
  vector <vector <int>> gr;
  vector <int> pos_type; // Grundy function
  pair <int, int> to_cut;
};

int main()
{
  int n, r;
  cin >> n >> r;
  r--;
  Graph_grundy game(n);
  map<pair <int, int>, int> edges;
  for (int i = 1; i < n; i++)
  {
    int left, right;
    cin >> left >> right;
    left--; right--;
    game.add_edge(left, right);
    game.add_edge(right, left);
    edges[{left, right}] = i;
    edges[{right, left}] = i;
  }

  game.dfs_calc(r);
  if (game.get_pos_type(r))
  {
    cout << 1 << '\n';
    cout << edges[game.get_to_cut()];
  }
  else
  {
    cout << 2 << '\n';
  }

  return 0;
}