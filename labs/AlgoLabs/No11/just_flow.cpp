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
};

int dfs(int v, int min_cap, int t, vector<vector<int>>& gr, vector<bool>& used, vector<Edge>& edges)
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
        edges.emplace_back(Edge{ a, b, c, 0, size, size + 1 });     // straight
        gr[a].push_back(size);
        edges.emplace_back(Edge{ b, a, c, 0, size + 1, size });     // gay
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

    cout << max_flow << '\n';
    for (int i = 0; i < edges.size(); i += 2)
    {
        Edge& e = edges[i];
        if (!e.flow)
            cout << -edges[i + 1].flow << '\n';
        else
            cout << e.flow << '\n';
    }

    return 0;
}