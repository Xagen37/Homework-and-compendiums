#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define double long double

struct Node;

void tnh(Node& curr, const vector<Node>& nodes);
void tnh_d(Node& curr, vector<Node>& nodes);
void relu(Node& curr, const vector<Node>& nodes);
void relu_d(Node& curr, vector<Node>& nodes);
void mul(Node& curr, const vector<Node>& nodes);
void mul_d(Node& curr, vector<Node>& nodes);
void sum(Node& curr, const vector<Node>& nodes);
void sum_d(Node& curr, vector<Node>& nodes);
void had(Node& curr, const vector<Node>& nodes);
void had_d(Node& curr, vector<Node>& nodes);

struct Node
{
    string op;
    vector<int> param;
    int n = 0;
    int m = 0;
    vector<vector<double>> res = vector<vector<double>>(n, vector<double>(m));
    vector<vector<double>> diff = vector<vector<double>>(n, vector<double>(m));
    void (*compute)(Node& curr, const vector<Node>& nodes) = nullptr;
    void (*diff_f)(Node& curr, vector<Node>& nodes) = nullptr;

    Node(string s, vector<int> params)
        : op(s)
        , param(params)
    {
        switch (op[0])
        {
            case 'v':
            {
                n = param[0];
                m = param[1];
                diff.resize(n, vector<double>(m));
                break;
            }
            case 't':
            {
                compute = tnh;
                diff_f = tnh_d;
                break;
            }
            case 'r':
            {
                compute = relu;
                diff_f = relu_d;
                break;
            }
            case 'm':
            {
                compute = mul;
                diff_f = mul_d;
                break;
            }
            case 's':
            {
                compute = sum;
                diff_f = sum_d;
                break;
            }
            case 'h':
            {
                compute = had;
                diff_f = had_d;
                break;
            }
        }
    }
};

void tnh(Node& curr, const vector<Node>& nodes)
{
    const Node& arg = nodes[curr.param.front()];
    curr.n = arg.n;
    curr.m = arg.m;
    curr.res.resize(curr.n, vector<double>(curr.m));
    curr.diff.resize(curr.n, vector<double>(curr.m));
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            curr.res[i][j] += tanhl(arg.res[i][j]);
        }
    }
}

void tnh_d(Node& curr, vector<Node>& nodes)
{
    Node& arg = nodes[curr.param.front()];
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            arg.diff[i][j] += curr.diff[i][j] * (1.0 - (curr.res[i][j] * curr.res[i][j]));
        }
    }
}

void relu(Node& curr, const vector<Node>& nodes)
{
    double alpha = curr.param[0];//1.0 / curr.param[0];
    const Node& arg = nodes[curr.param[1]];
    curr.n = arg.n;
    curr.m = arg.m;
    curr.res.resize(curr.n, vector<double>(curr.m));
    curr.diff.resize(curr.n, vector<double>(curr.m));
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            curr.res[i][j] += arg.res[i][j] >= 0.0 ? arg.res[i][j] : arg.res[i][j] / alpha;//* alpha;
        }
    }
}

void relu_d(Node& curr, vector<Node>& nodes)
{
    double alpha = curr.param[0];//1.0 / curr.param[0];
    Node& arg = nodes[curr.param[1]];
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            arg.diff[i][j] += arg.res[i][j] >= 0.0 ? curr.diff[i][j] : curr.diff[i][j] / alpha;// * alpha;
        }
    }
}

void mul(Node& curr, const vector<Node>& nodes)
{
    const Node& x = nodes[curr.param[0]];
    const Node& y = nodes[curr.param[1]];
    curr.n = x.n;
    curr.m = y.m;
    curr.res.resize(curr.n, vector<double>(curr.m));
    curr.diff.resize(curr.n, vector<double>(curr.m));
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            for (int k = 0; k < x.m; k++)
            {
                curr.res[i][j] += x.res[i][k] * y.res[k][j];
            }
        }
    }
}

void mul_d(Node& curr, vector<Node>& nodes)
{
    Node& x = nodes[curr.param[0]];
    Node& y = nodes[curr.param[1]];
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < x.m; j++)
        {
            double sum_res = 0.0;
            for (int k = 0; k < curr.m; k++)
            {
                sum_res += curr.diff[i][k] * y.res[j][k];
            }
            x.diff[i][j] += sum_res;
        }
    }
    for (int i = 0; i < y.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            double sum_res = 0.0;
            for (int k = 0; k < curr.n; k++)
            {
                sum_res += curr.diff[k][j] * x.res[k][i];
            }
            y.diff[i][j] += sum_res;
        }
    }
}

void sum(Node& curr, const vector<Node>& nodes)
{
    curr.n = nodes[curr.param[0]].n;
    curr.m = nodes[curr.param[0]].m;
    curr.res.resize(curr.n, vector<double>(curr.m));
    curr.diff.resize(curr.n, vector<double>(curr.m));
    for (int id : curr.param)
    {
        for (int i = 0; i < curr.n; i++)
        {
            for (int j = 0; j < curr.m; j++)
            {
                curr.res[i][j] += nodes[id].res[i][j];
            }
        }
    }
}

void sum_d(Node& curr, vector<Node>& nodes)
{
    for (int id : curr.param)
    {
        for (int i = 0; i < curr.n; i++)
        {
            for (int j = 0; j < curr.m; j++)
            {
                nodes[id].diff[i][j] += curr.diff[i][j];
            }
        }
    }
}

void had(Node& curr, const vector<Node>& nodes)
{
    curr.n = nodes[curr.param[0]].n;
    curr.m = nodes[curr.param[0]].m;
    curr.res.resize(curr.n, vector<double>(curr.m, 1.0));
    curr.diff.resize(curr.n, vector<double>(curr.m));
    for (int id : curr.param)
    {
        for (int i = 0; i < curr.n; i++)
        {
            for (int j = 0; j < curr.m; j++)
            {
                curr.res[i][j] *= nodes[id].res[i][j];
            }
        }
    }
}

void had_d(Node& curr, vector<Node>& nodes)
{
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            for (int id1 = 0; id1 < curr.param.size(); id1++)
            {
                double mul_res = 1;
                for (int id2 = 0; id2 < curr.param.size(); id2++)
                {
                    if (id1 != id2)
                    {
                        mul_res *= nodes[curr.param[id2]].res[i][j];
                    }
                }
                nodes[curr.param[id1]].diff[i][j] += mul_res * curr.diff[i][j];
            }
        }
    }
}

int main()
{
    int n, m, k; cin >> n >> m >> k;

    vector<Node> computs;
    for (int i = 0; i < n; i++)
    {
        string op; cin >> op;
        switch (op[0])
        {
            case 'v':
            {
                int r, c; cin >> r >> c;
                computs.emplace_back(op, vector<int>{ r, c });
                break;
            }
            case 't':
            {
                int x; cin >> x;
                computs.emplace_back(op, vector<int>{ x - 1 });
                break;
            }
            case 'r':
            {
                int a, x; cin >> a >> x;
                computs.emplace_back(op, vector<int>{ a, x - 1 });
                break;
            }
            case 'm':
            {
                int a, b; cin >> a >> b;
                computs.emplace_back(op, vector<int>{ a - 1, b - 1 });
                break;
            }
            case 's': //fallthrough
            case 'h':
            {
                int l; cin >> l;
                vector<int> params(l);
                for (int z = 0; z < l; z++)
                {
                    cin >> params[z];
                    params[z]--;
                }
                computs.emplace_back(op, params);
                break;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        vector<vector<double>> matrix(computs[i].n, vector<double>(computs[i].m));
        for (int r = 0; r < matrix.size(); r++)
        {
            for (int c = 0; c < matrix[r].size(); c++)
            {
                cin >> matrix[r][c];
            }
        }
        computs[i].res = move(matrix);
    }

    for (int i = m; i < n; i++)
    {
        computs[i].compute(computs[i], computs);
    }

    for (int i = n - k; i < n; i++)
    {
        Node& in = computs[i];
        for (int r = 0; r < in.diff.size(); r++)
        {
            for (int c = 0; c < in.diff[r].size(); c++)
            {
                cin >> in.diff[r][c];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (computs[i].op != "var")
            computs[i].diff_f(computs[i], computs);
    }

    cout << setprecision(20);

    for (int i = n - k; i < n; i++)
    {
        Node& out = computs[i];
        for (int r = 0; r < out.res.size(); r++)
        {
            for (int c = 0; c < out.res[r].size(); c++)
            {
                cout << out.res[r][c] << ' ';
            }
            cout << '\n';
        }
    }

    for (int i = 0; i < m; i++)
    {
        Node& out = computs[i];
        for (int r = 0; r < out.res.size(); r++)
        {
            for (int c = 0; c < out.res[r].size(); c++)
            {
                cout << out.diff[r][c] << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}