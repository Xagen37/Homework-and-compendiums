#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const vector <vector <long long int>> stirling =
{
  {}
, {1}
, {-1, 1}
, {2, -3, 1}
, {-6, 11, -6, 1}
, {24, -50, 35, -10, 1}
, {-120, 274, -225, 85, -15, 1}
, {720, -1764,	1624,	-735,	175,	-21,	1}
, {-5040,	13068,	-13132,	6769,	-1960,	322,	-28,	1}
, {40320,	-109584,	118124,	-67284,	22449,	-4536,	546,	-36,	1}
, {-362880, 1026576, -1172700, 723680, -269325, 63273, -9450, 870, -45, 1}
};

struct Graph
{
  Graph(int n)
    : gr(n)
    , polynom(n + 1, 0)
  {}

  void add_edge(int left, int right)
  {
    gr[left].insert(right);
    gr[right].insert(left);
  }

  vector <long long int> part(int k)
  {
    vector <set<int>> partition(k);
    long long int pt_i = part_helper(partition, 0);
    vector <long long int> res(k, 0);
    for (size_t i = 0; i < res.size(); i++)
    {
      res[i] = pt_i * stirling[k][i];
    }
    return res;
  }

  int analyze(const vector <set<int>>& partition)
  {
    for (const auto& curr : partition)
    {
      if (curr.empty()) { return 0; }
      for (auto it1 : curr)
      {
        for (auto it2 : curr)
        {
          if (gr[it1].count(it2))
          {
            return 0;
          }
        }
      }
    }
    return 1;
  }

  long long int part_helper(vector <set <int>>& partition, int curr_v)
  {
    if (curr_v >= gr.size())
    {
      return analyze(partition);
    }
    else
    {
      long long int sum = 0;
      for (size_t i = 0; i < partition.size(); i++)
      {
        partition[i].insert(curr_v);
        sum += part_helper(partition, curr_v + 1);
        partition[i].erase(curr_v);
        if (partition[i].empty())
        {
          break;
        }
      }
      return sum;
    }
  }

  vector <long long int> f_zykov()
  {
    for (int i = 1; i <= gr.size(); i++)
    {
      vector <long long int> res = part(i);
      for (int k = 0; k < res.size(); k++)
      {
        polynom[k + 1] += res[k];
      }
    }
    return polynom;
  }
private:
  vector <set <int>> gr;
  vector <long long int> polynom;
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
  auto answ = g.f_zykov();
  cout << n << '\n';
  for (int i = answ.size() - 1; i >= 0; i--)
  {
    cout << answ[i] << ' ';
  }
  return 0;
}