#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const long long int EPS = 1;
const long long int SIGMA = 11;
const string acids = "ACDEFGHIKLMNPQRSTVWY";
vector<vector<long long int>> scorings(20, vector<long long int>(20));
const string blossom =
"4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2 \
 0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2 \
 -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3 \
-1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2 \
-2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3 \
0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3 \
-2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2 \
-1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1 \
-1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2 \
-1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1 \
-1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1 \
-2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2 \
-1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3 \
-1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1 \
-1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2 \
1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2 \
0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2 \
0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1 \
-3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2 \
-2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7";

using story_node = pair<string, string>;

int main()
{
    istringstream blossom_parse(blossom);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            blossom_parse >> scorings[i][j];
        }
    }

    string v, w; cin >> v >> w;
    int n = v.size(), m = w.size();
    vector<vector<long long int>> inserts(n + 1, vector<long long int>(m + 1, -1e9));
    vector<vector<long long int>> deletes(n + 1, vector<long long int>(m + 1, -1e9));
    vector<vector<long long int>> matches(n + 1, vector<long long int>(m + 1, -1e9));

    vector<vector<story_node>> story_i(n + 1, vector<story_node>(m + 1)); // 0
    vector<vector<story_node>> story_d(n + 1, vector<story_node>(m + 1)); // 1
    vector<vector<story_node>> story_m(n + 1, vector<story_node>(m + 1)); // 2

    matches[0][0] = inserts[0][0] = deletes[0][0] = 0;
    matches[1][0] = matches[0][1] = deletes[0][1] = inserts[1][0] = -SIGMA;
    for (int i = 2; i <= max(n, m); i++)
    {
        if (i <= n)
        {
            deletes[i][0] = inserts[i][0] = matches[i][0] = inserts[i - 1][0] - EPS;
        }

        if (i <= m)
        {
            deletes[0][i] = inserts[0][i] = matches[0][i] = deletes[0][i - 1] - EPS;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (inserts[i - 1][j] - EPS > matches[i - 1][j] - SIGMA)
            {
                inserts[i][j] = inserts[i - 1][j] - EPS;
                story_i[i][j].first = story_i[i - 1][j].first + v[i - 1];
                story_i[i][j].second = story_i[i - 1][j].second + '-';
            }
            else
            {
                inserts[i][j] = matches[i - 1][j] - SIGMA;
                story_i[i][j].first = story_m[i - 1][j].first + v[i - 1];
                story_i[i][j].second = story_m[i - 1][j].second + '-';
            }

            if (deletes[i][j - 1] - EPS > matches[i][j - 1] - SIGMA)
            {
                deletes[i][j] = deletes[i][j - 1] - EPS;
                story_d[i][j].first = story_d[i][j - 1].first + '-';
                story_d[i][j].second = story_d[i][j - 1].second + w[j - 1];
            }
            else
            {
                deletes[i][j] = matches[i][j - 1] - SIGMA;
                story_d[i][j].first = story_m[i][j - 1].first + '-';
                story_d[i][j].second = story_m[i][j - 1].second + w[j - 1];
            }

            if (deletes[i][j] > inserts[i][j])
            {
                matches[i][j] = deletes[i][j];
                story_m[i][j] = story_d[i][j];
            }
            else
            {
                matches[i][j] = inserts[i][j];
                story_m[i][j] = story_i[i][j];
            }

            int pos_v = acids.find(v[i - 1]);
            int pos_w = acids.find(w[j - 1]);

            if (matches[i - 1][j - 1] + scorings[pos_v][pos_w] > matches[i][j])
            {
                matches[i][j] = matches[i - 1][j - 1] + scorings[pos_v][pos_w];
                story_m[i][j].first = story_m[i - 1][j - 1].first + v[i - 1];
                story_m[i][j].second = story_m[i - 1][j - 1].second + w[j - 1];
            }
        }
    }

    cout << matches[n][m] << '\n';

    story_node answ = story_m[n][m];

    cout << answ.first << '\n' << answ.second;
    return 0;
}