#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    using pll = pair<long long int, long long int>;

    long long int k; cin >> k;
    long long int n; cin >> n;

    vector<vector<long long int>> objs(k);
    vector<pll> all(n);

    for (int i = 0; i < n; i++)
    {
        long long int x, y;
        cin >> x >> y;
        y--;
        objs[y].push_back(x);
        all[i] = { x, y };
    }

    sort(all.begin(), all.end(), [](const pll& l, const pll& r) { return l.first < r.first; });

    vector<long long int> sums(k);
    vector<long long int> counts(k);
    for (int i = 0; i < k; i++)
    {
        sort(objs[i].begin(), objs[i].end());
        sums[i] = accumulate(objs[i].begin(), objs[i].end(), 0LL);
        counts[i] = objs[i].size();
    }

    // ------------------------------------------------------------------------
    vector<long long int> inners(k);
    for (int i = 0; i < k; i++)
    {
        long long int before = sums[i];
        long long int after = 0;
        for (int z = 0; z < objs[i].size(); z++)
        {
            before -= objs[i][z];

            inners[i] += z * objs[i][z];
            inners[i] -= (objs[i].size() - 1LL - z) * objs[i][z];
            inners[i] += before;
            inners[i] -= after;

            after += objs[i][z];
        }
    }
    long long int inclass = accumulate(inners.begin(), inners.end(), 0LL);
    // ------------------------------------------------------------------------
    long long int before = accumulate(sums.begin(), sums.end(), 0LL);
    long long int after = 0;
    vector<long long int> sums_before = move(sums);
    vector<long long int> cnts_before = move(counts);
    vector<long long int> sums_after(k);
    vector<long long int> cnts_after(k);
    long long int outclass = 0;
    
    for (int i = 0; i < n; i++)
    {
        long long int x = all[i].first;
        long long int y = all[i].second;
        
        before -= x;
        sums_before[y] -= x;
        cnts_before[y]--;

        outclass += (i - cnts_after[y]) * x;
        outclass -= (n - 1LL - i - cnts_before[y]) * x;
        outclass += before - sums_before[y];
        outclass -= after - sums_after[y];

        after += x;
        sums_after[y] += x;
        cnts_after[y]++;
    }
    

    cout << inclass << '\n' << outclass;

    return 0;
}