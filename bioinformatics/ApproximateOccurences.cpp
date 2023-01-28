#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool check_approximate(const string& lhs, const string& rhs, int d)
{
    int sz = min(lhs.size(), rhs.size());
    int cnt = 0;
    for (int i = 0; i < sz; i++)
    {
        if (lhs[i] != rhs[i])
        {
            cnt++;
        }
    }
    return cnt <= d;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string text; cin >> text;
    vector<string> patts;
    string in;
    while (cin >> in)
    {
        if (in == "break")
            break;

        patts.push_back(in);
    }

    int d; cin >> d;

    vector<pair<string, int>> suffs;
    for (int i = 0; i < text.size(); i++)
    {
        suffs.push_back({ text.substr(i), i });
    }

    sort(suffs.begin(), suffs.end(), [](const pair<string, int>& lhs, const pair<string, int>& rhs)
                                      { return lhs.first < rhs.first; });

    vector<int> finds;
    for (int i = 0; i < suffs.size(); i++)
    {
        for (const string& patt : patts)
        {
            if (suffs[i].first.size() >= patt.size() &&
                check_approximate(suffs[i].first, patt, d))
            {
                finds.push_back(suffs[i].second);
            }
        }
    }
    sort(finds.begin(), finds.end());

    for (const int pos : finds)
    {
        cout << pos << ' ';
    }

    return 0;
}