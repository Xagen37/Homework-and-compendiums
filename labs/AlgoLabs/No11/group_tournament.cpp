#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Edge
{
    int from, to;
    int cap, flow;
    int id, rev_id;
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

int map_ch(char val)
{
    switch (val)
    {
    case 'W': return 3;
    case 'L': return 0;
    case 'w': return 2;
    case 'l': return 1;
    case '.': return 0;
    default: 
        cerr << val << endl; throw "wtf";
    }
}

char map_res(int val)
{
    switch (val)
    {
    case 3: return 'W';
    case 2: return 'w';
    case 1: return 'l';
    case 0: return 'L';
    default:
        cerr << val << endl; throw "wtf";
    }
}

int main()
{
    int n; cin >> n;
    vector <vector <char>> field(n, vector<char>(n));
    for (int i = 0; i < n; i++)
    {
        string inp;
        cin >> inp;
        for (int j = 0; j < n; j++)
        {
            field[i][j] = inp[j];
        }
    }
    vector <int> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i];
    vector <int> actual(n, 0);
    vector <vector <int>> gr(n + 1);
    vector <Edge> edges;
    map<int, pair<int, int>> games;
    int start = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;

            actual[i] += map_ch(field[i][j]);

            if (field[i][j] == '.' && i < j)
            {
                int g_id = gr.size();
                int e_size = edges.size();
                gr.emplace_back(vector<int>());

                edges.emplace_back(Edge{ start, g_id,         // straight
                                        3, 0,
                                        e_size, e_size + 1 });
                edges.emplace_back(Edge{ g_id, start,         // reversed
                                        0, 0,
                                        e_size + 1, e_size });
                gr[start].push_back(e_size);
                gr[g_id].push_back(e_size + 1);

                games[g_id] = { i + 1, j + 1 };
                e_size = edges.size();
                edges.emplace_back(Edge{ g_id, i + 1,         // straight
                                         3, 0,
                                         e_size, e_size + 1 });
                edges.emplace_back(Edge{ i + 1, g_id,         // reversed
                                         0, 0,
                                         e_size + 1, e_size});
                gr[g_id].push_back(e_size);
                gr[i + 1].push_back(e_size + 1);

                e_size = edges.size();
                edges.emplace_back(Edge{ g_id, j + 1,         // straight
                                         3, 0,
                                         e_size, e_size + 1 });
                edges.emplace_back(Edge{ j + 1, g_id,        // reversed
                                         0, 0,
                                         e_size + 1, e_size });
                gr[g_id].push_back(e_size);
                gr[j + 1].push_back(e_size + 1);
            }
        }
    }
    vector <int> diff(n);
    for (int i = 0; i < n; i++)
        diff[i] = points[i] - actual[i];
    int fin = gr.size();
    gr.emplace_back(vector<int>());
    for (int i = 1; i <= n; i++)
    {
        int e_size = edges.size();
        edges.emplace_back(Edge{ i, fin,         // straight
                                diff[i - 1], 0,
                                e_size, e_size + 1 });
        edges.emplace_back(Edge{ fin, i,        // reversed
                                0, 0,
                                e_size + 1, e_size });
        gr[i].push_back(e_size);
        gr[fin].push_back(e_size + 1);
    }

    for (vector <bool> used(gr.size(), false);
        dfs(start, INT_MAX, fin, gr, used, edges);
        used.assign(gr.size(), false));

    for (auto game : games)
    {
        vector<int> e_ids = gr[game.first];
        vector<int> e_real;
        for (int i = 0; i < e_ids.size(); i++)
        {
            if (edges[e_ids[i]].cap == 3)
                e_real.push_back(e_ids[i]);
        }

        Edge e1 = edges[e_real[0]], e2 = edges[e_real[1]];
        field[e1.to - 1][e2.to - 1] = map_res(e1.flow);
        field[e2.to - 1][e1.to - 1] = map_res(e2.flow);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << field[i][j];
        }
        cout << '\n';
    }

    return 0;
}