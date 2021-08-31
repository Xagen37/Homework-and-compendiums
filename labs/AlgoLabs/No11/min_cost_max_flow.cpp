#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

using type_t = long long int;

struct Edge
{
    type_t from, to;
    type_t cap, flow, cost;
    type_t id, rev_id;
};

vector<type_t> dijkstra(type_t s, vector<vector<type_t>>& gr, vector<Edge>& edges, vector<pair<type_t, type_t>>& par)
{
    set <pair <type_t, type_t>> q;
    vector<type_t> dp(gr.size(), LLONG_MAX);
    dp[s] = 0;
    q.insert({ s, 0 });
    par[s] = { -1, -1 };

    while (!q.empty())
    {
        type_t v = q.begin()->second;
        q.erase(q.begin());

        for (type_t u : gr[v])
        {
            type_t& to = edges[u].to;
            type_t& cost = edges[u].cost;

            if (edges[u].flow < edges[u].cap && dp[v] + cost < dp[to])
            {
                q.erase({ dp[to], to });
                dp[to] = dp[v] + cost;
                q.insert({ dp[to], to });
                par[to] = { v, u };
            }
        }
    }

    return dp;
}

struct Result
{
    bool is_ok;
    type_t flow;
    vector<type_t> path;
};

Result get_path(type_t s, type_t t, vector<vector<type_t>>& gr, vector<Edge>& edges, vector<pair<type_t, type_t>>& par, vector<long long int>& dp)
{
    if (dp[t] == LLONG_MAX)
        return Result{ false, 0, vector<type_t>() };
    vector<type_t> path;
    pair<type_t, type_t> curr_v = par[t];
    while (curr_v.first != -1)
    {
        path.push_back(curr_v.second);
        curr_v = par[curr_v.first];
    }
    reverse(path.begin(), path.end());
    type_t min_cap = LLONG_MAX;
    for (type_t e : path)
    {
        min_cap = min(min_cap, edges[e].cap - edges[e].flow);
    }
    return { true, min_cap, path };
}

void min_cost_max_flow(type_t s, type_t t, vector<vector<type_t>>& gr, vector<Edge>& edges)
{
    while (true)
    {
        vector<pair<type_t, type_t>> par(gr.size());
        vector<type_t> dp = dijkstra(s, gr, edges, par);
        Result res = get_path(s, t, gr, edges, par, dp);
        if (!res.is_ok)
            break;
        for (type_t e : res.path)
        {
            edges[e].flow += res.flow;
            edges[edges[e].rev_id].flow -= res.flow;
        }
    }
}

int main()
{
    type_t n, m;
    cin >> n >> m;
    vector<vector<type_t>> gr(n);
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        type_t from, to, cap, cost;
        cin >> from >> to >> cap >> cost; from--; to--;
        type_t e_size = edges.size();
        edges.emplace_back(Edge{ from, to,      // straight
                                 cap, 0, cost,
                                 e_size, e_size + 1 });
        edges.emplace_back(Edge{ to, from,      // reversed
                                 0, 0, -cost,
                                 e_size + 1, e_size });
        gr[from].push_back(e_size);
        gr[to].push_back(e_size + 1);
    }

    min_cost_max_flow(0, n - 1, gr, edges);
    type_t answ = 0;
    for (int i = 0; i < edges.size(); i += 2)
    {
        answ += (edges[i].flow * edges[i].cost);
    }
    cout << answ;

    return 0;
}