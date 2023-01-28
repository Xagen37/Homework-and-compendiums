#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using obj_t = pair<vector<int>, int>;
int main()
{
    int n, m; cin >> n >> m;

    vector<obj_t> kirill(n);
    for (int i = 0; i < n; i++)
    {
        kirill[i].first.resize(m);
        for (int j = 0; j < m; j++)
        {
            cin >> kirill[i].first[j];
        }
        cin >> kirill[i].second;
    }

    vector<int> koefs(m + 1);
    for (int i = 0; i <= m; i++)
    {
        cin >> koefs[i];
    }

    cout << setprecision(20);

    for (int i = 0; i < n; i++)
    {
        vector<double> grad(m + 1, 1.0);
        copy(kirill[i].first.begin(), kirill[i].first.end(), grad.begin());
        const double y_expect = inner_product(grad.begin(), grad.end(), koefs.begin(), 0.0);
        const double y_real = kirill[i].second;
        
        if (abs(y_expect - y_real) < 1e-7)
        {
            for (int z = 0; z <= m; z++)
            {
                cout << 0.0 << ' ';
            }
            cout << '\n';
        }
        else
        {
            const double sign = (y_expect - y_real) / abs(y_expect - y_real);
            const double numerator = abs(y_expect) * abs(y_real) + y_expect * y_real;
            const double sum = abs(y_expect) + abs(y_real);
            const double denumerator = abs(y_expect) * sum * sum;
            for (int z = 0; z <= m; z++)
            {
                grad[z] *= sign * numerator / denumerator;
                cout << grad[z] << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}