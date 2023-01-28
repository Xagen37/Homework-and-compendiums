#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    long long int n; cin >> n;

    if (n == 1)
    {
        cout << 0.0;
        return 0;
    }

    vector<long long int> xs(n);
    vector<long long int> ys(n);

    for (int i = 0; i < n; i++)
    {
        cin >> xs[i] >> ys[i];
    }

    unordered_map<long long int, long long int> x_ranks;
    unordered_map<long long int, long long int> y_ranks;

    vector<long long int> x_copy(xs);
    vector<long long int> y_copy(ys);

    sort(x_copy.begin(), x_copy.end());
    sort(y_copy.begin(), y_copy.end());

    for (int i = 0; i < n; i++)
    {
        x_ranks.insert({ x_copy[i], i + 1LL });
        y_ranks.insert({ y_copy[i], i + 1LL });
    }

    vector<long long int> d_sq(n);
    for (int i = 0; i < n; i++)
    {
        long long int diff = x_ranks[xs[i]] - y_ranks[ys[i]];
        d_sq[i] = diff * diff;
    }

    long long int sum = accumulate(d_sq.begin(), d_sq.end(), 0LL);

    double corr = 1.0 - 6.0 * sum / (n * (n * n - 1.0));

    cout << setprecision(20) << corr;

    return 0;
}