#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct Edge
{
    int from, to, weight;
    Edge():
        from(0),
        to(0),
        weight(0)
        {}
 
    Edge(int f, int t, int w):
        from(f),
        to(t),
        weight(w)
        {}
};
 
bool cmp(const Edge & left, const Edge & right)
{
    return left.weight < right.weight;
}
 
vector <Edge> edges;
vector <int> parent;
vector <int> r;
 
int root(int x)
{
    if (parent[x] == -1)
    {
        return x;
    }
    else
    {
        return parent[x] = root(parent[x]);
    }
}
 
void m_union(int x, int y)
{
    int a = root(x);
    int b = root(y);
 
    if (a == b)
    {
        return;
    }
    else
    {
        if (r[a] > r[b])
        {
            parent[b] = a;
        }
        else
        {
            if (r[b] > r[a])
            {
                parent[a] = b;
            }
            else
            {
                parent[b] = a;
                r[a]++;
            }
        }
    }
}
 
bool m_find(int x, int y)
{
    return (root(x) == root(y));
}
 
int main()
{
    int n, m;
    cin >> n >> m;
    edges.resize(m);
    parent.resize(n, -1);
    r.resize(n, 0);
 
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges[i] = Edge(a, b, c);
    }
    sort(edges.begin(), edges.end(), cmp);
 
    long long int answ = 0;
    for (int i = 0; i < edges.size(); i++)
    {
        int x = edges[i].from;
        int y = edges[i].to;
 
        if (!m_find(x, y))
        {
            m_union(x, y);
            answ += edges[i].weight;
        }
    }
 
    cout << answ;
    return 0;
}