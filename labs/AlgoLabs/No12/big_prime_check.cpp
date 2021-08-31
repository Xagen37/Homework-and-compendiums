// launch with "GNU C++17 (64)"
#include <cmath>
#include <iostream>
#include <random>
 
using namespace std;
mt19937_64 r;
__int128 pow_pow (__int128 base, __int128 p, __int128 mod)
{
    if (p == 1)
        return base;
    if (p % 2)
        return (base * pow_pow(base, p - 1, mod)) % mod;
    else 
    {
        __int128 temp = pow_pow(base, p / 2, mod);
        return (temp * temp) % mod;
    }
}
 
pair<__int128, __int128> two_s_and_t(__int128 n)
{
    int cnt = 0;
    while(!(n % 2))
    {
        n /= 2;
        cnt++;
    }
    return {cnt, n};
}
 
bool is_prime(__int128 n)
{
    if (n < 2) 
        return false;
    if (n < 4)
        return true;
    
    pair<__int128, __int128> d = two_s_and_t(n - 1);
    int k = 4;  // test your luck
    for (int lolo = 0; lolo < k; lolo++)
    {
        __int128 a = 2 + r() % (n - 3);
        __int128 x = pow_pow(a, d.second, n);
        if (x == 1 || x == n - 1)
            continue;
        bool flag = false;
        for (int pepe = 0; pepe < d.first - 1; pepe++)
        {
            x = pow_pow(x, 2, n);
            if (x == 1) 
                return false;
            else if (flag = (x == n - 1))
                break;
        }
        if (flag)
            continue;
        else
            return false;
    }
    return true;
}
 
int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++)
    {
        long long int a; cin >> a;
        cout << (is_prime(a) ? "YES" : "NO") << '\n';
    }
    
    return 0;
}