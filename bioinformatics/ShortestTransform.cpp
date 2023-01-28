#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// odd - tail, even - head
using edge_t = pair<int, int>;
enum class Color { BLACK, RED };

void cycle_dfs(int v, Color color, vector<int>& used, vector<int>& cycle, map<pair<int, Color>, int>& matrix)
{
    used[v - 1] = 1;
    cycle.push_back(v);
    int u = matrix[{ v, color }];
    if (u == cycle.front())
    { return; }

    cycle_dfs(u, color == Color::BLACK ? Color::RED : Color::BLACK, used, cycle, matrix);
}

void dfs(int v, int end, vector<int>& path, set<int>& used, map<int, int>& matrix)
{
    path.push_back(v % 2 ? (v + 1) / -2 : v / 2);
    int next = matrix[v];
    used.insert(next);
    if (next == end)
    { return; }

    next = next % 2 ? next + 1 : next - 1;
    used.insert(next);
    dfs(next, end, path, used, matrix);
}

vector<int> parse(string genes)
{
    genes.erase(0, 1);
    genes.pop_back();

    istringstream in(genes);
    vector<int> parsed;
    int gene = -1;

    while (in >> gene)
    { parsed.push_back(gene); }

    return parsed;
}

vector<vector<edge_t>> ge_to_gr(const vector<vector<int>>& ge)
{
    vector<vector<edge_t>> gr;
    for (const vector<int>& part : ge)
    {
        vector<edge_t> curr;
        for (int gene : part)
        {
            if (gene > 0)
                curr.push_back({ gene * 2 - 1, gene * 2 });
            else
                curr.push_back({ abs(gene) * 2, abs(gene) * 2 - 1 });
        }
        gr.push_back(curr);
    }
    return gr;
}

vector<vector<int>> gr_to_ge(const vector<edge_t>& gr)
{
    set<int> used_v;
    map<int, int> matrix;
    for (const edge_t& edge : gr)
    {
        matrix[edge.first] = edge.second;
        matrix[edge.second] = edge.first;
    }

    vector<vector<int>> ge;
    for (const edge_t& edge : gr)
    {
        if (!used_v.count(edge.first))
        {
            used_v.insert(edge.first);
            int end = edge.first % 2 ? edge.first + 1 : edge.first - 1;
            vector<int> path;
            dfs(edge.first, end, path, used_v, matrix);
            ge.push_back(path);
        }
    }

    return ge;
}

string ge_to_str(const vector<vector<int>>& ge)
{
    string ret;
    for (const vector<int>& part : ge)
    {
        ret.push_back('(');
        for (int gene : part)
        {
            if (gene > 0)
                ret.push_back('+');

            ret.append(to_string(gene));
            ret.push_back(' ');
        }
        ret.pop_back();
        ret.push_back(')');
    }
    return ret;
}

vector<edge_t> with_colored(const vector<vector<int>>& ge)
{
    vector<vector<edge_t>> gr = ge_to_gr(ge);
    vector<edge_t> edges;
    for (const vector<edge_t>& curr : gr)
    {
        for (int i = 0; i < curr.size(); i++)
        {
            edges.push_back({ curr[i].second, curr[(i + 1) % curr.size()].first });
        }
    }
    return edges;
}

vector<vector<int>> find_cycles(const vector<edge_t>& black, const vector<edge_t>& red)
{
    vector<int> used(black.size() + red.size());
    map<pair<int, Color>, int> matrix;

    for (const edge_t& edge : black)
    {
        matrix[{edge.first, Color::BLACK}] = edge.second;
        matrix[{edge.second, Color::BLACK}] = edge.first;
    }
    for (const edge_t& edge : red)
    {
        matrix[{edge.first, Color::RED}] = edge.second;
        matrix[{edge.second, Color::RED}] = edge.first;
    }

    vector<vector<int>> cycles;

    for (int i = 0; i < used.size(); i++)
    {
        if (!used[i])
        {
            vector<int> cycle;
            cycle_dfs(i + 1, Color::BLACK, used, cycle, matrix);
            cycles.push_back(cycle);
        }
    }
    return cycles;
}

vector<vector<int>> swap_edges(vector<edge_t>& gr, const vector<int>& cycle)
{
    set<edge_t> bad;
    bad.insert({ cycle[0], cycle[1] });
    bad.insert({ cycle[2], cycle[3] });

    vector<edge_t> new_gr;
    for (edge_t& edge : gr)
    {
        if (!bad.count(edge))
        {
            new_gr.push_back(edge);
        }
    }

    new_gr.push_back({ cycle[0], cycle[3] });
    new_gr.push_back({ cycle[1], cycle[2] });

    return gr_to_ge(new_gr);
}

int main()
{
    string from; getline(cin, from);
    string to; getline(cin, to);

    vector<vector<int>> ge_from = { parse(from) };
    vector<vector<int>> ge_to = { parse(to) };

    vector<edge_t> red = with_colored(ge_to);
    cout << from << '\n';

    while (from != to)
    {
        vector<edge_t> black = with_colored(ge_from);
        vector<vector<int>> cycles = find_cycles(black, red);
        for (const vector<int>& cycle : cycles)
        {
            if (cycle.size() > 2)
            {
                ge_from = swap_edges(black, cycle);
                from = ge_to_str(ge_from);
                cout << from << '\n';
                break;
            }
        }
    }

    return 0;
}