#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Hash
{
    size_t operator()(const pair<long long int, long long int>& arg) const
    {
        return arg.first * 1000000 + arg.second;
    }
};

int main()
{
    using pll = pair<long long int, long long int>;

    int kx, ky; cin >> kx >> ky;
    int n; cin >> n;

    vector<long long int> cntx(kx);
    unordered_map<pll, long long int, Hash> obj_cnts;
    vector<pll> objs(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        objs[i] = { x, y };
        obj_cnts[objs[i]]++;
        cntx[x]++;
    }

    unordered_set<pll, Hash> used;
    double entropy = 0.0;
    for (const pll& obj : objs)
    {
        if (used.count(obj))
            continue;
        used.insert(obj);

        const long long int x = obj.first;
        const double p = obj_cnts[obj] / static_cast<double>(cntx[x]);
        entropy -= (obj_cnts[obj] / static_cast<double>(n)) * log(p);
    }

    cout << setprecision(20) << entropy;

    return 0;
}