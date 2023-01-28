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

    int k1, k2; cin >> k1 >> k2;
    int n; cin >> n;

    vector<pll> objs(n);
    vector<long long int> cnts1(k1);
    vector<long long int> cnts2(k2);
    unordered_map<pll, long long int, Hash> obj_cnts;
    for (int i = 0; i < n; i++)
    {
        int x1, x2; 
        cin >> x1 >> x2;
        x1--; x2--;
        cnts1[x1]++;
        cnts2[x2]++;
        objs[i] = { x1, x2 };
        obj_cnts[objs[i]]++;
    }

    double hi = 0.0;
    double ni_rest = n;
    unordered_set<pll, Hash> used;
    for (int i = 0; i < n; i++)
    {
        if (used.count(objs[i]))
            continue;
        used.insert(objs[i]);

        const long long int x1 = objs[i].first;
        const long long int x2 = objs[i].second;

        const double ni = cnts1[x1] * cnts2[x2] / static_cast<double>(n);
        const double diff = obj_cnts[objs[i]] - ni;
        hi += diff * diff / ni;
        ni_rest -= ni;
    }
    hi += ni_rest;

    cout << setprecision(20) << hi;

    return 0;
}