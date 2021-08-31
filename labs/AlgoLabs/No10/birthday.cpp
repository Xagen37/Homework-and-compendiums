#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Graph
{
    Graph() = default;

    Graph(int n)
        : gr(n)
        , matching(n, -1)
    {}

    void add_edge(int from, int to)
    {
        gr[from].push_back(to);
    }

    void kuhn()
    {
        for (int i = 0; i < gr.size(); i++)
        {
            vector <int> used(gr.size(), 0);
            dfs(i, used);
        }
    }

    bool dfs(int v, vector <int>& used)
    {
        if (used[v]) { return false; }
        used[v] = 1;
        for (int i = 0; i < inverted[v].size(); i++)
        {
            if (matching[inverted[v][i]] == -1 || dfs(matching[inverted[v][i]], used))
            {
                matching[inverted[v][i]] = v;
                return true;
            }
        }
        return false;
    }

    void check_dfs(int v, vector<vector<int>>& g, vector<bool>& taken)
    {
        taken[v] = 1;
        for (auto u : g[v])
        {
            if (!taken[u])
            {
                check_dfs(u, g, taken);
            }
        }
    }

    vector <vector <int>> gr;
    vector <vector <int>> inverted;
    vector <int> matching;
};

void solve()
{
    int m, n; cin >> n >> m;
    Graph g;
    g.gr.resize(n);
    g.matching.resize(m, -1);
    g.inverted.resize(n);
    vector <vector<bool>> inverted_matrix(n, vector<bool>(m, false));

    for (int man = 0; man < n; man++)
    {
        int woman;
        for (cin >> woman; woman != 0; cin >> woman)
        {
            woman--;
            inverted_matrix[man][woman] = true;
            g.add_edge(man, woman);
        }
    }

    for (int man = 0; man < n; man++)
    {
        for (int woman = 0; woman < m; woman++)
        {
            if (!inverted_matrix[man][woman])
            {
                g.inverted[man].push_back(woman);
            }
        }
    }

    g.kuhn();
    set<int> used;
    vector <vector<bool>> matchings(n, vector<bool>(m, false));
    for (int i = 0; i < m; i++)
    {
        if (g.matching[i] != -1)
        {
            matchings[g.matching[i]][i] = true;
            used.insert(g.matching[i]);
        }
    }
   
    vector <vector <int>> new_graph(n + m);
    for (int man = 0; man < n; man++)
    {
        for (int woman = 0; woman < g.inverted[man].size(); woman++)
        {
            if (matchings[man][g.inverted[man][woman]])
            {
                new_graph[g.inverted[man][woman] + n].push_back(man);
            }
            else
            {
                new_graph[man].push_back(g.inverted[man][woman] + n);
            }
        }
    }

    vector <bool> taken(n + m, false);
    for (int i = 0; i < n; i++)
    {
        if (!used.count(i))
        {
            g.check_dfs(i, new_graph, taken);
        }
    }

    set<int> covered;
    for (int i = 0; i < n + m; i++)
    {
        if (i < n)
        {
            if (!taken[i])
                covered.insert(i);
        }
        else
        {
            if (taken[i])
                covered.insert(i);
        }

    }

    set<int> men, women;
    for (int i = 0; i < n + m; i++)
    {
        if (!covered.count(i))
        {
            if (i < n)
                men.insert(i);
            else
                women.insert(i - n);
        }
    }

    cout << men.size() + women.size() << '\n';
    cout << men.size() << ' ' << women.size() << '\n';

    for (auto man : men)
    {
        cout << man + 1 << ' ';
    } 
    cout << '\n';
    for (auto woman : women)
    {
        cout << woman + 1 << ' ';
    }
    cout << '\n';
}

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        solve();
        cout << '\n';
    }

    return 0;
}