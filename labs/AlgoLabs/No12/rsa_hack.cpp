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
    int k = 10;
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
 
__int128 wide_euclid (__int128 a, __int128 b, __int128& x, __int128& y)
{
    if (!a)
    {
        x = 0;
        y = 1;
        return b;
    }
    __int128 x1, y1;
    __int128 gcd = wide_euclid(b % a, a, x1, y1);
    x = y1 - x1 * (b / a);
    y = x1;
    return gcd;
}
 
long long int reverse(__int128 n, __int128 mod)
{
    __int128 x, y;
    long long gcd = wide_euclid(n, mod, x, y);
    return (x % mod + mod) % mod;
}
 
int main()
{
    long long int n, e, c;
    cin >> n >> e >> c;
    
    long long int d;
    for (__int128 p = 2; p * p < n; p++)
    {
        if (!is_prime(p))
            continue;
        long long int pp = p;
        if (n % pp)
            continue;
            
        long long int qq = n / pp;
        __int128 q = qq;
        if (!is_prime(q))
            continue;
            
        d = reverse(e, (pp - 1) * (qq - 1));
        break;
    }
    
    cout << static_cast<long long int>(pow_pow(c, d, n));
    return 0;
}