#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Edge
{
    int from, to;
    long long int cap, flow;
    int id, rev_id;
    bool is_straight;
};

int dfs(int v, long long int min_cap, int t, const vector<vector<int>>& gr, vector<bool>& used, vector<Edge>& edges)
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

void get_path(int v, int t, bool& found, const vector<vector<int>>& gr, vector<Edge>& edges, vector<int>& path)
{
    if (v == t)
    {
        found = 1;
        return;
    }

    for (int i = 0; i < gr[v].size(); i++)
    {
        Edge& e = edges[gr[v][i]];
        if (e.is_straight && !found && e.flow == 1)
        {
            e.flow = 0;
            path.push_back(e.to);
            get_path(e.to, t, found, gr, edges, path);
        }
    }
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;
    
    vector <vector <int>> gr(n);
    vector <Edge> edges;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y; x--; y--;

        int size = edges.size();
        edges.emplace_back(Edge{ x, y, 1, 0, size, size + 1, true });     // straight
        gr[x].push_back(size);
        edges.emplace_back(Edge{ y, x, 0, 0, size + 1, size, false });     // gay
        gr[y].push_back(size + 1);
    }

    for (vector <bool> used(n);
        dfs(s, INT_MAX, t, gr, used, edges);
        used.assign(n, false));

    long long int max_flow = 0;
    for (const Edge& e : edges)
    {
        max_flow += (e.from == s && e.is_straight) ? e.flow : 0;
    }

    if (max_flow <= 1)
    {
        cout << "NO";
        return 0;
    }

    vector<int> path1(1, s), path2(1, s);
    bool flag = false;
    get_path(s, t, flag, gr, edges, path1);
    flag = false;
    get_path(s, t, flag, gr, edges, path2);

    if (path1.back() != t || path2.back() != t)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << '\n';
    for (int i = 0; i < path1.size(); i++)
        cout << path1[i] + 1 << ' ';
    cout << '\n';
    for (int i = 0; i < path2.size(); i++)
        cout << path2[i] + 1 << ' ';

    return 0;
}