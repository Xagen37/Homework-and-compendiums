#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define SIZE 36

char dividers[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K' };
struct Node
{
  Node()
  {
    suff_link = -1;
    len = 0;
  }

  unordered_map <char, int> next;
  int suff_link;
  int len;
};

struct Trie
{
  Trie()
  {
    nodes.emplace_back(Node());
  }

  void add_string(const string& s)
  {
    for (int i = 0; i < s.size(); i++)
    {
      int curr = nodes.size();
      nodes.emplace_back(Node());
      nodes[curr].len = nodes[last].len + 1;
      int p;
      for (p = last; p != -1 && !nodes[p].next.count(s[i]); p = nodes[p].suff_link)
      {
        nodes[p].next[s[i]] = curr;
      }
      if (p == -1) { nodes[curr].suff_link = 0; }
      else
      {
        int q = nodes[p].next[s[i]];
        if (nodes[p].len + 1 == nodes[q].len) { nodes[curr].suff_link = q; }
        else
        {
          int clone = nodes.size();
          nodes.emplace_back(Node());
          nodes[clone].len = nodes[p].len + 1;
          nodes[clone].next = nodes[q].next;
          nodes[clone].suff_link = nodes[q].suff_link;
          nodes[q].suff_link = nodes[curr].suff_link = clone;
          for (; p != -1 && nodes[p].next[s[i]] == q; p = nodes[p].suff_link) 
          {
            nodes[p].next[s[i]] = clone; 
          }
        }
      }
      last = curr;
    }
  }

  string lcs(string t)
  {
    set<string> answ;

    int v, l, mx, mxpos;
    v = l = mx = mxpos = 0;
    for (int i = 0; i < t.length(); i++)
    {
      while (v && !nodes[v].next.count(t[i]))
      {
        v = nodes[v].suff_link;
        l = nodes[v].len;
      }
      if (nodes[v].next.count(t[i]))
      {
        v = nodes[v].next[t[i]];
        l++;
      }
      else
      {
        v = l = 0;
      }

      if (l >= mx)
      {
        if (l > mx)
        {
          answ.clear();
          mx = l;
          mxpos = i;
          answ.insert(t.substr(mxpos - mx + 1, mx));
        }
        else
        {
          answ.insert(t.substr(i - l + 1, l));
        }
      }
    }

    return *answ.begin();
  }

  vector <Node> nodes;
  int last = 0;
};

int main()
{
  string s, t;
  cin >> s >> t;
  Trie bor;
  bor.add_string(s + '$');
  
  cout << bor.lcs(t);
  return 0;
}