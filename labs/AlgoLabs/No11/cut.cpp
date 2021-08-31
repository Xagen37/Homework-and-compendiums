#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Edge
{
    int from, to;
    int cap, flow;
    int id, rev_id;
    int num;
};

int dfs(int v, int min_cap, int t, const vector<vector<int>>& gr, vector<bool>& used, vector<Edge>& edges)
{
    if (v == t)
        return min_cap;

    used[v] = 1;
    for (int i = 0; i < gr[v].size(); i++)
    {
        Edge& e = edges[gr[v][i]];
        if (!used[e.to] && e.flow < e.cap)
        {
            int delta = dfs(e.to, min(min_cap, e.cap - e.flow), t, gr, used, edges);
            if (delta)
            {
                int temp = gr[v][i];
                edges[temp].flow += delta;
                edges[edges[temp].rev_id].flow -= delta;
                return delta;
            }
        }
    }

    return 0;
}

void min_cut(int v, const vector<vector<int>>& gr, vector<bool>& used, vector<Edge>& edges)
{
    used[v] = true;

    for (int i = 0; i < gr[v].size(); i++)
    {
        Edge& e = edges[gr[v][i]];

        if (!used[e.to] && e.flow < e.cap)
        {
            min_cut(e.to, gr, used, edges);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> gr(n);
    vector<Edge> edges;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c; a--; b--;
        int size = edges.size();
        edges.emplace_back(Edge{ a, b, c, 0, size, size + 1, i });     // straight
        gr[a].push_back(size);
        edges.emplace_back(Edge{ b, a, c, 0, size + 1, size, i });     // gay
        gr[b].push_back(size + 1);
    }

    int s = 0, t = n - 1;
    long long int max_flow = 0;


    for (vector <bool> used(n);
        dfs(s, INT_MAX, t, gr, used, edges);
        used.assign(n, false));

    for (const int& v : gr[0])
    {
        max_flow += abs(edges[v].flow);
    }

    vector<bool> used(n, 0);
    min_cut(s, gr, used, edges);

    vector<int> answ;
    for (int i = 0; i < edges.size(); i += 2)
    {
        if (used[edges[i].from] != used[edges[i].to])
        {
            answ.push_back(edges[i].num);
        }
    }
    cout << answ.size() << ' ' << max_flow << '\n';

    for (const int& i : answ)
    {
        cout << i + 1 << ' ';
    }
    return 0;
}