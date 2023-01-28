#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

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
void sigma(Node& curr, const vector<Node>& nodes);
void sigma_d(Node& curr, vector<Node>& nodes);

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
                if (op[1] == 'u')
                {
                    compute = sum;
                    diff_f = sum_d;
                }
                else
                {
                    compute = sigma;
                    diff_f = sigma_d;
                }
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

void sigma(Node& curr, const vector<Node>& nodes)
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
            curr.res[i][j] = 1.0 / (1 + exp(-arg.res[i][j]));
        }
    }
}

void sigma_d(Node& curr, vector<Node>& nodes)
{
    Node& arg = nodes[curr.param.front()];
    for (int i = 0; i < curr.n; i++)
    {
        for (int j = 0; j < curr.m; j++)
        {
            arg.diff[i][j] += curr.res[i][j] * (1 - curr.res[i][j]) * curr.diff[i][j];
        }
    }
}

void read_mat(vector<vector<double>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cin >> matrix[i][j];
        }
    }
}

void print_mat(const vector<vector<double>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    cout << setprecision(20);
    int n; cin >> n;
    vector<Node> network;
    vector<vector<double>> matrix(n, vector<double>(n));
    vector<vector<double>> vec(n, vector<double>(1));
    //1
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;
    //2
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;
    //3
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;
    //4
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(matrix);
    network.emplace_back("var", vector<int>{ n, n });
    network.back().res = matrix;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;

    int m; cin >> m;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;
    read_mat(vec);
    network.emplace_back("var", vector<int>{ n, 1 });
    network.back().res = vec;

    swap(network[13], network[12]);

    vector<int> fs;
    vector<int> cs = { 12 };
    vector<int> hs = { 13 };
    vector<int> xs;
    for (int i = 0; i < m; i++)
    {
        int node_pos = network.size();
        read_mat(vec);
        network.emplace_back("var", vector<int>{ n, 1 });
        network.back().res = vec;
        int start = 21 * i + 14;
        int prev_h = start - 1;
        int prev_c = prev_h - 1;
        vector<int> block_ids;
        for (int k = 0; k < 4; k++)
        {
            int w = network.size();
            network.emplace_back("mul", vector<int>{ k * 3, node_pos });
            int u = network.size();
            network.emplace_back("mul", vector<int>{ k * 3 + 1, prev_h });
            block_ids.push_back(network.size());
            network.emplace_back("sum", vector<int>{ w, u, k * 3 + 2 });
        }
        int f = network.size();
        network.emplace_back("sigma", vector<int>{ block_ids[0] });
        int i_ = network.size();
        network.emplace_back("sigma", vector<int>{ block_ids[1] });
        int o = network.size();
        network.emplace_back("sigma", vector<int>{ block_ids[2] });
        int ta_nya = network.size();
        network.emplace_back("thn", vector<int>{ block_ids[3] });
        int i_mult = network.size();
        network.emplace_back("had", vector<int>{ i_, ta_nya });
        int prev_f = network.size();
        network.emplace_back("had", vector<int>{ f, prev_c });
        int curr_c = network.size();
        network.emplace_back("sum", vector<int>{ prev_f, i_mult });
        int curr_h = network.size();
        network.emplace_back("had", vector<int>{ o, curr_c });

        fs.push_back(o);
        cs.push_back(curr_c);
        hs.push_back(curr_h);
        xs.push_back(start);
    }

    for (int i = 0; i < network.size(); i++)
    {
        if (network[i].op != "var")
            network[i].compute(network[i], network);
    }

    read_mat(network[hs[m]].diff);
    read_mat(network[cs[m]].diff);
    for (int i = fs.size() - 1; i >= 0; i--)
    {
        read_mat(network[fs[i]].diff);
    }

    for (int i = network.size() - 1; i >= 0; i--)
    {
        if (network[i].op != "var")
            network[i].diff_f(network[i], network);
    }

    for (int i = 0; i < fs.size(); i++)
    {
        print_mat(network[fs[i]].res);
    }
    print_mat(network[hs[m]].res);
    print_mat(network[cs[m]].res);

    for (int i = xs.size() - 1; i >= 0; i--)
    {
        print_mat(network[xs[i]].diff);
    }
    print_mat(network[hs[0]].diff);
    print_mat(network[cs[0]].diff);
    for (int i = 0; i < 12; i++)
    {
        print_mat(network[i].diff);
    }

    return 0;
}