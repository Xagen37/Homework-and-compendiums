#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    struct Vert
    {
        int hour = 0;
        int minute = 0;
        pair<int, int> pos;

        int time() const
        {
            return hour * 60 + minute;
        }
    };

    Graph() = default;

    Graph(int n)
        : gr(n)
        , matching(n, -1)
    {}

    void add_edge(int from, int to)
    {
        gr[from].push_back(to);
    }

    void add_edges(vector <Vert>& input, double speed)
    {
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = i + 1; j < input.size(); j++)
            {
                if (d(input[i].pos, input[j].pos) <= speed * (input[j].time() - input[i].time()))
                {
                    add_edge(i, j);
                }
            }
        }
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

    double d(pair <int, int> const& from, pair <int, int> const& to)
    {
        return hypot(to.first - from.first, to.second - from.second);
    }

    vector <vector <int>> gr;
    vector <int> matching;
};

int main()
{
    int n;
    double speed;
    cin >> n >> speed;
    speed /= 60;
    
    Graph g(n);

    vector <Graph::Vert> input(n);
    char garbage;
    for (int i = 0; i < n; i++)
    {
        int hour, minute; cin >> hour >> garbage >> minute;
        pair<int, int> place;
        cin >> place.first >> place.second;

        input[i] = { hour, minute, place };
    }

    sort(input.begin(), input.end(), [](const Graph::Vert& lhs, const Graph::Vert& rhs)
        {
            return lhs.time() < rhs.time();
        }
    );
    
    g.add_edges(input, speed);
    g.kuhn();

    int cnt = 0;
    for (int i = 0; i < g.matching.size(); i++)
    {
        if (g.matching[i] != -1)
        { cnt++; }
    }

    cout << n - cnt;
    return 0;
}