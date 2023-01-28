#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    int k; cin >> k;
    int n; cin >> n;

    vector<vector<long long int>> objs(k);
    for (int i = 0; i < n; i++)
    {
        long long int x, y;
        cin >> x >> y;
        x--;
        objs[x].push_back(y);
    }

    double D = 0.0;
    for (int i = 0; i < k; i++)
    {
        if (objs[i].size() == 0)
            continue;

        const double cnt = objs[i].size();
        const long long int sum = accumulate(objs[i].begin(), objs[i].end(), 0LL);
        const double E = sum / cnt;
        double sq_diff = 0;
        for (long long int& obj : objs[i])
        {
            double diff = obj - E;
            sq_diff += diff * diff;
        }
        D += sq_diff / n;  // (sq_diff / cnt) * (cnt / n);
    }

    cout << setprecision(20) << D;

    return 0;
};