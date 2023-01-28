#include <iomanip>
#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    int n; cin >> n;
    vector<long long int> xs(n);
    vector<long long int> ys(n);

    for (int i = 0; i < n; i++)
    {
        cin >> xs[i] >> ys[i];
    }

    long double aver_x = accumulate(xs.begin(), xs.end(), 0LL) / static_cast<long double>(n);
    long double aver_y = accumulate(ys.begin(), ys.end(), 0LL) / static_cast<long double>(n);

    long double numerator = 0.0;
    long double sum_x = 0.0;
    long double sum_y = 0.0;
    for (int i = 0; i < n; i++)
    {
        long double x_diff = xs[i] - aver_x;
        long double y_diff = ys[i] - aver_y;
        numerator += x_diff * y_diff;
        sum_x += x_diff * x_diff;
        sum_y += y_diff * y_diff;
    }

    cout << setprecision(20);
    if (abs(sum_x) <= 1e-6 || abs(sum_y) <= 1e-6)
    {
        cout << 0.0;
    }
    else
    {
        long double denominator = sqrt(sum_x * sum_y);
        long double corr = numerator / denominator;
        cout << corr;
    }

    return 0;
}