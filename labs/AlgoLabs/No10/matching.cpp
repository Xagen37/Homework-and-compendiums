#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    Graph(int n, int m)
        : gr(n)
        , matching(m, -1)
    {}

    void add_edges(int from, const vector <int>& to)
    {
        gr[from].insert(gr[from].end(), to.begin(), to.end());
    }

    vector<int> kuhn()
    {
        for (int i = 0; i < gr.size(); i++)
        {
            vector <int> used(gr.size(), 0);
            dfs(i, used);
        }
        return matching;
    }

private:
    bool dfs(int v, vector <int>& used)
    {
        if (used[v]) { return false; }
        used[v] = 1;
        for (int i = 0; i < gr[v].size(); i++)
        {
            if (matching[gr[v][i]] == -1 || dfs(matching[gr[v][i]], used))
            {
                matching[gr[v][i]] = v;
                return true;
            }
        }
        return false;
    }

    vector <vector <int>> gr;
    vector <int> matching;
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n, m);

    for (int i = 0; i < n; i++)
    {
        vector <int> verts;
        int val; cin >> val;
        for (; val != 0; cin >> val)
        {
            val--;
            verts.push_back(val);
        }
        g.add_edges(i, verts);
    }

    auto answ = g.kuhn();
    int cnt = 0;
    for (int i = 0; i < answ.size(); i++)
    {
        if (answ[i] != -1)
            cnt++;
    }
    cout << cnt << '\n';
    for (int i = 0; i < answ.size(); i++)
    {
        if (answ[i] != -1)
            cout << answ[i] + 1 << ' ' << i + 1 << '\n';
    }
    return 0;
}