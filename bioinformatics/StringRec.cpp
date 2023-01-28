#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using pss = pair<string, string>;

struct Hash
{
    size_t operator()(const pss& arg) const
    {
        return std::hash<string>{}(arg.first) * 1e9 + std::hash<string>{}(arg.second);
    }
};

unordered_map<pss, vector<pss>, Hash> graph;

vector<pss> find_euler()
{
    vector<pss> path;
    stack<pss> st;

    int max_cnt = -1;
    pss start;
    unordered_set<pss, Hash> begins;
    unordered_set<pss, Hash> ends;
    for (const auto& vert : graph)
    {
        begins.insert(vert.first);
        ends.insert(vert.second.begin(), vert.second.end());
    }
    for (const pss& p : begins)
    {
        if (!ends.count(p))
        {
            start = p;
            break;
        }
    }

    if (start.first.empty())
    {
        start = graph.begin()->first;
    }

    st.push(start);
    while (!st.empty())
    {
        const pss& curr = st.top();
        if (graph[curr].empty())
        {
            path.push_back(curr);
            st.pop();
        }
        else
        {
            pss next = graph[curr].back();
            graph[curr].pop_back();
            st.push(next);
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

string get_answer(int d)
{
    const vector<pss> path = find_euler();
    string answer = path[0].first;
    for (int i = 1; i <= d + 1; i++)
    {
        answer += path[i].first.back();
    }
    answer += path[0].second;
    for (int i = 1; i < path.size(); i++)
    {
        answer += path[i].second.back();
    }

    return answer;
}

int main()
{
    int k, d; cin >> k >> d;
    vector<pss> reads;
    string text;
    while (cin >> text)
    {
        if (text == "break")
            break;

        reads.emplace_back(text.substr(0, k), text.substr(k + 1));
    }

    const int vertex_len = k - 1; //k / 2 + 1;
    for (const pss& read : reads)
    {
        for (int i = 0; i < k - vertex_len; i++)
        {
            const pss prefs = { read.first.substr(0, vertex_len), read.second.substr(0, vertex_len) };
            const pss sufs = { read.first.substr(i + 1, vertex_len), read.second.substr(i + 1, vertex_len) };

            graph[prefs].push_back(sufs);
        }
    }

    cout << get_answer(d);

    return 0;
}