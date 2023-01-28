#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    string genom; cin >> genom;
    string answ;
    vector<vector<int>> dp(genom.size(), vector<int>(genom.size()));

    for (int i = 1; i < genom.size(); i++)
    {
        for (int j = i + 1; j < genom.size(); j++)
        {
            if (genom[i] == genom[j] &&
                (i > 0 && j > 0 && (j - i) > dp[i - 1][j - 1]))
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > answ.size())
                {
                    answ = genom.substr(i - dp[i][j] + 1, dp[i][j]);
                }
            }
        }
    }

    if (!answ.size())
        answ = genom[0];

    cout << answ;
}

// Operation "Suffix tree" failed, proceed with plan B

/*const string chars = "ACGT";
using state_t = pair<int, int>;

struct Node
{
    int l = 0, r = 0;
    int link = -1;
    int parent = -1;
    unordered_map<char, int> edges;

    int len()
    { return r - l; }
};

vector<Node> tree(1);
state_t state = { 0, 0 };
string genom;

int get(Node& node, char c)
{
    return node.edges.count(c) ? node.edges[c] : -1;
}

state_t go(state_t curr, int l, int r)
{
    while (l < r)
    {
        if (curr.second == tree[curr.first].len())
        {
            curr = { get(tree[curr.first], genom[l]), 0 };
            if (curr.first == -1)
                return curr;
        }
        else
        {
            int v = curr.first;
            if (genom[tree[v].l + curr.second] != genom[l])
            {
                return { -1, -1 };
            }
            if (r - l < tree[v].len() - curr.second)
            {
                return { v, curr.second + r - l };
            }
            l += tree[v].len() - curr.second;
            curr.second = tree[v].len();
        }
    }
    return curr;
}

int split(state_t curr)
{
    if (curr.second == tree[curr.first].len())
        return curr.first;
    if (!curr.second)
        return tree[curr.first].parent;

    Node v = tree[curr.first];
    int idx = tree.size();
    tree.push_back(Node());
    tree.back().parent = v.parent;
    tree.back().l = v.l;
    tree.back().r = v.l + curr.second;

    tree[v.parent].edges[genom[v.l]] = idx;
    tree[idx].edges[genom[v.l + curr.second]] = curr.first;
    tree[curr.first].parent = idx;
    tree[curr.first].l += curr.second;

    return idx;
}

int link(int v)
{
    if (tree[v].link != -1)
    {
        return tree[v].link;
    }
    if (tree[v].parent == -1)
    {
        return 0;
    }
    int to = link(tree[v].parent);
    tree[v].link = split(go({ to, tree[to].len() }, tree[v].l + (tree[v].parent == 0 ? 1 : 0), tree[v].r));
    return tree[v].link;
}

void tree_add_char(int pos)
{
    while (true)
    {
        state_t curr = go(state, pos, pos + 1);
        if (curr.first != -1)
        {
            state = curr;
            return;
        }

        int mid = split(state);
        int leaf = tree.size();
        tree.push_back(Node());
        tree.back().l = pos;
        tree.back().r = genom.size();
        tree.back().parent = mid;

        tree[mid].edges[genom[pos]] = leaf;
        state.first = link(mid);
        state.second = tree[state.first].len();
        if (!mid)
            break;
    }
}

void init_tree()
{
    for (int i = 0; i < genom.size(); i++)
    {
        tree_add_char(i);
    }
}

int main()
{
    cin >> genom;
    genom += '$';

    init_tree();
    vector<int> d(tree.size(), INT_MAX);
    string answ;
    queue<pair<int, string>> q; q.push({ 0, "" });
    d[0] = 0;

    while (!q.empty())
    {
        pair<int, string> v = q.front(); q.pop();
        for (const pair<char, int>& edge : tree[v.first].edges)
        {
            int to = edge.second;
            if (d[to] > d[v.first] + 1)
            {
                d[to] = d[v.first] + 1;
                q.push({ to, v.second + edge.first });
                if (tree[to].edges.size() >= 2)
                {
                    string curr = v.second + edge.first;
                    if (curr.size() > answ.size())
                        answ = curr;
                }
            }
        }
    }

    if (answ.empty() || (answ.size() == 1 && answ[0] == '$'))
        cout << genom[0];

    cout << answ;

    return 0;
}*/
