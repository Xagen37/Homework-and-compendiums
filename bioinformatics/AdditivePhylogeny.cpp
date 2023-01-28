#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
using edge_t = pair<int, double>;
int cnt;

double limblen(const vector<vector<double>>& matrix, int n)
{
    double minval = DBL_MAX;
    for (int j = 0; j < matrix.size(); j++)
    {
        for (int k = j + 1; k < matrix.size(); k++)
        {
            if (j == n || k == n)
                continue;

            double curr = (matrix[n][k] + matrix[n][j] - matrix[j][k]) / 2.0;
            if (curr < minval)
                minval = curr;
        }
    }
    return minval;
}

map<int, vector<edge_t>> AddPhyl(vector<vector<double>> matrix)
{
    if (matrix.size() == 2)
    {
        map<int, vector<edge_t>> tree;
        tree[0].push_back({ 1, matrix[0][1] });
        tree[1].push_back({ 0, matrix[0][1] });
        return tree;
    }

    int n = matrix.size() - 1;
    double limb = limblen(matrix, n);
    for (int j = 0; j < n; j++)
    {
        matrix[j][n] -= limb;
        matrix[n][j] = matrix[j][n];
    }
    int i_leaf = -1, k_leaf = -1;
    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            if (matrix[i][k] == matrix[i][n] + matrix[n][k])
            {
                i_leaf = i;
                k_leaf = k;
                goto cycle_break;
            }
        }
    }
cycle_break:
    int x = matrix[i_leaf][n];
    auto matrix_copy = matrix;
    for (int i = 0; i < matrix_copy.size(); i++)
    {
        matrix_copy[i].pop_back();
    }
    matrix_copy.pop_back();
    map<int, vector<edge_t>> tree = AddPhyl(matrix_copy);

    vector<double> d(cnt, DBL_MAX);
    vector<int> prev(cnt, -1);
    queue<int> q; q.push(i_leaf);
    d[i_leaf] = 0;
    while (!q.empty())
    {
        int v = q.front(); q.pop();
        for (const edge_t& edge : tree[v])
        {
            if (d[edge.first] > d[v] + edge.second)
            {
                d[edge.first] = d[v] + edge.second;
                prev[edge.first] = v;
                if (edge.first != k_leaf)
                {
                    q.push(edge.first);
                }
                else
                {
                    int curr = k_leaf;
                    int par = v;

                    while (x < d[par])
                    {
                        curr = par;
                        par = prev[par];
                    }

                    if (x == d[par])  // node already exists
                    {
                        tree[par].push_back({ n, limb });
                        tree[n].push_back({ par, limb });
                    }
                    else  // need to create node
                    {
                        tree[n].push_back({ cnt, limb });
                        tree[cnt].push_back({ n, limb });

                        for (int i = 0; i < tree[par].size(); i++)
                        {
                            if (tree[par][i].first == curr)
                            {
                                tree[par][i].first = cnt;
                                tree[par][i].second = x - d[par];
                                tree[cnt].push_back({ par, x - d[par] });
                                break;
                            }
                        }

                        for (int i = 0; i < tree[curr].size(); i++)
                        {
                            if (tree[curr][i].first == par)
                            {
                                tree[curr][i].first = cnt;
                                tree[curr][i].second = d[curr] - x;
                                tree[cnt].push_back({ curr, d[curr] - x});
                                break;
                            }
                        }

                        cnt++;
                    }
                    return tree;
                }
            }
        }
    }
    throw exception();
    return tree;
}

int main()
{
    int n; cin >> n;
    cnt = n;
    vector<vector<double>> add_matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
            cin >> add_matrix[i][k];
    }

    auto tree = AddPhyl(add_matrix);
    for (int i = 0; i < tree.size(); i++)
    {
        const vector<edge_t>& edges = tree[i];
        for (const edge_t& edge : edges)
        {
            cout << i << "->" << edge.first << ':' << edge.second << '\n';
        }
    }

    return 0;
}
