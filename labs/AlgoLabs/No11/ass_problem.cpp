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

pair<type_t, vector<type_t>> bulgarian(vector<vector<type_t>>& gr)
{
    int size = gr.size();
    vector<type_t> u(size), v(size);
    vector<type_t> p(size);
    vector<type_t> way(size);

    for (int i = 1; i < size; i++)
    {
        p[0] = i;
        vector<type_t> min_v(size, LLONG_MAX);
        vector<bool> used(size, false);
        int j = 0;
        while (p[j])
        {
            used[j] = true;
            type_t curr_i = p[j], curr_j = 0;
            type_t delta = LLONG_MAX;
            for (int k = 1; k < size; k++)
            {
                if (used[k]) continue;
                type_t A = gr[curr_i][k] - u[curr_i] - v[k];
                if (A < min_v[k])
                {
                    min_v[k] = A;
                    way[k] = j;
                }
                if (min_v[k] < delta)
                {
                    delta = min_v[k];
                    curr_j = k;
                }
            }

            for (int k = 0; k < size; k++)
            {
                if (used[k])
                {
                    u[p[k]] += delta;
                    v[k] -= delta;
                }
                else
                    min_v[k] -= delta;
            }

            j = curr_j;
        }

        while (j)
        {
            type_t next_j = way[j];
            p[j] = p[next_j];
            j = next_j;
        }
    }
    vector<type_t> answ(size);
    for (int k = 1; k < size; k++)
    {
        answ[p[k]] = k;
    }
    return { -v[0], answ };
}

int main()
{
    int n; cin >> n;
    vector<vector<type_t>> gr(n + 1, vector<type_t>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> gr[i][j];
        }
    }
    auto res = bulgarian(gr);
    cout << res.first << '\n';
    for (int i = 1; i < res.second.size(); i++)
    {
        cout << i << ' ' << res.second[i] << '\n';
    }

    return 0;
}