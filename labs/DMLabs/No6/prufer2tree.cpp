#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main()
{
  int n; cin >> n;
  vector <int> code(n - 2);
  for (int i = 0; i < n - 2; i++)
  {
    cin >> code[i];
    code[i]--;
  }

  vector <pair <int, int>> answ;
  vector <int> edge_count(n, 1);
  for (auto it : code)
  {
    edge_count[it]++;
  }
  set <int> not_used;
  for (int i = 0; i < edge_count.size(); i++)
  {
    if (edge_count[i] == 1) { not_used.insert(i); }
  }

  for (int i = 0; i < code.size(); i++)
  {
    int mex = *not_used.begin(); 
    not_used.erase(not_used.begin());
    edge_count[code[i]]--;
    if (edge_count[code[i]] == 1) { not_used.insert(code[i]); }

    answ.push_back({ min(code[i], mex), max(code[i], mex) });
  }
  answ.push_back({ *(not_used.begin()), *(++not_used.begin()) });
  for (int i = 0; i < answ.size(); i++)
  {
    cout << answ[i].first + 1 << ' ' << answ[i].second + 1 << '\n';
  }

  return 0;
}