#include <algorithm>
#include <iostream>
 
using namespace std;
using ull = long long int;
 
// Wide Euclid is walking, but he is always in frame
ull wide_euclid (ull a, ull b, ull& x, ull& y)
{
    if (!a)
    {
        x = 0;
        y = 1;
        return b;
    }
    ull x1, y1;
    ull gcd = wide_euclid(b % a, a, x1, y1);
    x = y1 - x1 * (b / a);
    y = x1;
    return gcd;
}
 
int main()
{
    ull a, b, n, m;
    cin >> a >> b >> n >> m;
    ull M = n * m;
    ull x, y; // x for n, y for m
    wide_euclid(n, m, x, y);
    ull answ = (a * y * m + b * x * n) % M;
    while(answ < 0)
    {
        answ += M;
    }
    cout << answ;
    return 0;
}