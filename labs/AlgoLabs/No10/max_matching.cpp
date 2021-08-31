#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Graph
{
    using ENTRY = std::pair<int, int>;

    void kuhn_left()
    {
        sort(weight_left.begin(), weight_left.end(), greater<ENTRY>());
        for (int i = 0; i < left.size(); i++)
        {
            vector <int> used(left.size(), 0);
            dfs(weight_left[i].second, used, left, matching_left);
        }
    }

    void kuhn_right()
    {
        sort(weight_right.begin(), weight_right.end(), greater<ENTRY>());
        for (int i = 0; i < right.size(); i++)
        {
            vector <int> used(right.size(), 0);
            dfs(weight_right[i].second, used, right, matching_right);
        }
    }

    static bool dfs(int v, vector <int>& used, vector<vector<int>>& gr, vector<int>& matching)
    {
        if (used[v]) { return false; }
        used[v] = 1;
        for (int i = 0; i < gr[v].size(); i++)
        {
            if (matching[gr[v][i]] == -1 || dfs(matching[gr[v][i]], used, gr, matching))
            {
                matching[gr[v][i]] = v;
                return true;
            }
        }
        return false;
    }

    vector <vector <int>> left;
    vector <ENTRY> weight_left;
    vector <vector <int>> right;
    vector <ENTRY> weight_right;
    vector <int> matching_left, matching_right;
};

int main()
{
    map<std::pair<int, int>, int> edges;
    int n, m, e;
    cin >> n >> m >> e;

    Graph g;
    g.left.resize(n);
    g.right.resize(m);
    g.weight_left.resize(n);
    g.weight_right.resize(m);
    g.matching_left.resize(m, -1);
    g.matching_right.resize(n, -1);

    vector<int> weight_left_copy(n);
    for (int i = 0; i < n; i++)
    {
        int weight; cin >> weight;
        weight_left_copy[i] = weight;
        g.weight_left[i] = { weight, i };
    }

    vector<int> weight_right_copy(m);
    for (int i = 0; i < m; i++)
    {
        int weight; cin >> weight;
        weight_right_copy[i] = weight;
        g.weight_right[i] = { weight, i };
    }

    for (int i = 0; i < e; i++)
    {
        int l, r; cin >> l >> r;
        l--; r--;
        edges[{ l, r }] = i;
        g.left[l].push_back(r);
        g.right[r].push_back(l);
    }

    g.kuhn_left();
    set<int> left_in_match(g.matching_left.begin(), g.matching_left.end());
    left_in_match.erase(-1);

    g.kuhn_right();
    set<int> right_in_match(g.matching_right.begin(), g.matching_right.end());
    right_in_match.erase(-1);

    vector<vector<int>> brand_new_graph(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < g.left[i].size(); j++)
        {
            if (left_in_match.count(i) && right_in_match.count(g.left[i][j]))
            {
                brand_new_graph[i].push_back(g.left[i][j]);
            }
        }
    }
    vector<int> brand_new_matching(m, -1);
    vector<Graph::ENTRY> brand_new_weight(n, { 0, 0 });
    for (int i = 0; i < n; i++)
    {
        if (left_in_match.count(i))
        {
            brand_new_weight[i] = { weight_left_copy[i], i };
        }
    }
    sort(brand_new_weight.begin(), brand_new_weight.end(), greater<Graph::ENTRY>());

    for (int i = 0; i < n; i++)
    {
        vector<int> brand_new_used(n, 0);
        Graph::dfs(brand_new_weight[i].second, brand_new_used, brand_new_graph, brand_new_matching);
    }

    int answ_w = 0;
    vector<int> answ_e;
    for (int i = 0; i < m; i++)
    {
        if (brand_new_matching[i] != -1)
        {
            answ_w += weight_left_copy[brand_new_matching[i]] + weight_right_copy[i];
            answ_e.push_back(edges[{brand_new_matching[i], i}] + 1);
        }
    }

    cout << answ_w << '\n';
    cout << answ_e.size() << '\n';

    for (int i = 0; i < answ_e.size(); i++)
    {
        cout << answ_e[i] << " ";
    }
    return 0;
}