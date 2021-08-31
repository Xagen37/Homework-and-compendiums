#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge
{
    long long int from, to;
    long long int cap, flow;
    long long int id, rev_id;
    long long int x, y;
    bool is_vertex;
};

struct Cell
{
    long long int x, y;
    char c;
    long long int inv, outv;
};

long long int dfs(long long int v, long long int min_cap, long long int t, const vector<vector<long long int>>& gr, vector<bool>& used, vector<Edge>& edges)
{
    if (v == t)
        return min_cap;

    used[v] = 1;
    for (int i = 0; i < gr[v].size(); i++)
    {
        Edge& e = edges[gr[v][i]];
        if (!used[e.to] && e.flow < e.cap)
        {
            long long int delta = dfs(e.to, min(min_cap, e.cap - e.flow), t, gr, used, edges);
            if (delta)
            {
                long long int temp = gr[v][i];
                edges[temp].flow += delta;
                edges[edges[temp].rev_id].flow -= delta;
                return delta;
            }
        }
    }

    return 0;
}

void min_cut(long long int v, const vector<vector<long long int>>& gr, vector<bool>& used, vector<Edge>& edges)
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
    vector<vector<Cell>> map(n, vector<Cell>(m));
    vector<Edge> edges;
    vector<vector<long long int>> gr;
    pair<long long int, long long int> s, t;
    for (int i = 0; i < n; i++)
    {
        string inp; cin >> inp;
        for (int j = 0; j < m; j++)
        {
            if (inp[j] == '#')
            {
                map[i][j] = { i, j, '#', -1, -1 }; continue;
            }
            else if (inp[j] == 'A')
                s = { i, j };
            else if (inp[j] == 'B')
                t = { i, j };

            long long int gr_size = gr.size();
            gr.emplace_back(vector<long long int>());
            gr.emplace_back(vector<long long int>());
            Cell& temp = map[i][j] = { i, j, inp[j], gr_size, gr_size + 1 };

            long long int e_size = edges.size();
            edges.emplace_back(Edge{ temp.inv, temp.outv,       // straight
                                    (temp.c == '.') ? 1 : INT_MAX, 0,
                                     e_size, e_size + 1,
                                     i, j,
                                     true });
            edges.emplace_back(Edge{ temp.outv, temp.inv,       // gay
                                     0, 0,
                                     e_size + 1, e_size,
                                     i, j,
                                     true });

            gr[temp.inv].push_back(e_size);
            gr[temp.outv].push_back(e_size + 1);
        }
    }

    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};

    for (long long int x = 0; x < n; x++)
    {
        for (long long int y = 0; y < m; y++)
        {
            if (map[x][y].c != '#')
            {
                for (int i = 0; i < 4; i++)
                {
                    long long int new_x = x + dx[i];
                    long long int new_y = y + dy[i];

                    if (new_x >= 0 && new_x < n &&
                        new_y >= 0 && new_y < m &&
                        map[new_x][new_y].c != '#')
                    {
                        Cell& from = map[x][y];
                        Cell& to = map[new_x][new_y];

                        long long int e_size = edges.size();
                        edges.emplace_back(Edge{ from.outv, to.inv,     // straight
                                                 INT_MAX, 0,
                                                 e_size, e_size + 1,
                                                 to.x, to.y,
                                                 false });

                        edges.emplace_back(Edge{ to.inv, from.outv,     // I am tired of this joke. reversed
                                                 0, 0,
                                                 e_size + 1, e_size,
                                                 from.x, from.y,
                                                 false });

                        gr[from.outv].push_back(e_size);
                        gr[to.inv].push_back(e_size + 1);
                    }
                }
            }
        }
    }

    long long st = map[s.first][s.second].inv;
    long long fin = map[t.first][t.second].inv;

    for (vector<bool>used(gr.size(), false);
         dfs(st, INT_MAX + 10000LL, fin, gr, used, edges);
         used.assign(gr.size(), false));

    long long max_flow = 0;
    for (const int& v : gr[st])
    {
        max_flow += abs(edges[v].flow);
    }
    if (max_flow >= INT_MAX)
    {
        cout << -1;
        return 0;
    }

    cout << max_flow << '\n';
    vector<bool> used(gr.size(), 0);
    min_cut(st, gr, used, edges);

    vector<int> answ;
    for (int i = 0; i < edges.size(); i += 2)
    {
        if (edges[i].is_vertex && used[edges[i].from] != used[edges[i].to])
        {
            map[edges[i].x][edges[i].y].c = '+';
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j].c;
        }
        cout << '\n';
    }

    return 0;
}