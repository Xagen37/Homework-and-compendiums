#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string text; cin >> text;
    vector<string> patts;
    string in;
    while (cin >> in)
    {
        if (in == "break")
            break;

        patts.push_back(in);
    }

    vector<pair<string, int>> suffs;
    for (int i = 0; i < text.size(); i++)
    {
        suffs.push_back({ text.substr(i), i });
    }

    sort(suffs.begin(), suffs.end(), [](const pair<string, int>& lhs, const pair<string, int>& rhs)
                                      { return lhs.first < rhs.first; });

    set<int> finds;
    for (int i = 0; i < suffs.size(); i++)
    {
        for (const string& patt : patts)
        {
            if (suffs[i].first.starts_with(patt))
            {
                finds.insert(suffs[i].second);
            }
        }
    }

    for (const int pos : finds)
    {
        cout << pos << ' ';
    }

    return 0;
}