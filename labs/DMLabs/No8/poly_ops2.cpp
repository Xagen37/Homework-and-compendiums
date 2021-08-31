#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const static long long int MAGIC = 100;

long long int gcdex(long long int a, long long int b, long long int& x, long long int& y)
{
    if (!a)
    {
        x = 0;
        y = 1;
        return b;
    }
    long long int x1, y1;
    long long int d = gcdex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long int reverse_elem(long long int a, long long int mod)
{
    long long int x, y;
    long long int g = gcdex(a, mod, x, y);
    if (g != 1)
    { throw "what?"; }
    else
    {
        return (x % mod + mod) % mod;
    }
}

long long int frac_by_mod(long long int a, long long int b, long long int mod)
{
    return a * reverse_elem(b, mod) % mod;
}

long long int factorial(long long int n, long long int mod)
{
    long long int res = 1;
    for (int i = 1; i <= n; i++)
    {
        res = (res * i) % mod;
    }
    return res;
}

// из x/y по m
long long int choose(long long int x, long long int y, long long int m, long long int mod)
{
    if (!m) return 1;
    long long int n = frac_by_mod(x, y, mod);
    long long int denominator = factorial(m, mod);
    long long int numerator = n;
    for (int i = 1; i < m; i++)
    {
        numerator = (numerator * ((n - 1) % mod)) % mod;
        n--;
    }
    return frac_by_mod(numerator, denominator, mod);
}

struct Polynom
{
    constexpr static long long int MOD = 998244353;

    using type_t = long long int;

    Polynom(std::size_t degree)
        : coef(degree + 1, 0)
    {}

    Polynom(std::vector<type_t>&& other)
        : coef(std::move(other))
    {}

    Polynom(const Polynom& other)
        :coef(other.coef)
    {}

    Polynom(Polynom&& other)
        :coef(std::move(other.coef))
    {}

    Polynom& operator=(const Polynom& other)
    {
        this->coef = other.coef;
        return *this;
    }

    Polynom& operator=(Polynom&& other)
    {
        this->coef = std::move(other.coef);
        return *this;
    }

    Polynom operator+(const Polynom& other) const
    {
        Polynom res(std::max(other.degree(), degree()));
        std::size_t pos = 0;
        std::size_t min_size = std::min(other.degree(), degree()) + 1;
        for (; pos < min_size; pos++)
        {
            res[pos] = (other[pos] + coef[pos]) % MOD;
        }

        std::vector<type_t>& ref = (pos < coef.size()) ? coef : other.coef;
        for (; pos < ref.size(); pos++)
        {
            res[pos] = ref[pos];
        }

        return res;
    }

    Polynom operator*(const Polynom& other) const
    {
        Polynom res(other.degree() + degree());
        for (std::size_t i = 0; i < coef.size(); i++)
        {
            for (std::size_t j = 0; j < other->size(); j++)
            {
                res[i + j] += (coef[i] * other[j]) % MOD;
                res[i + j] %= MOD;
            }
        }

        return res;
    }

    Polynom operator* (const long long int& mult) const
    {
        Polynom res(degree());
        for (long long int i = 0; i < coef.size(); i++)
        {
            res[i] = (coef[i] * mult) % MOD;
        }
        return res;
    }

    Polynom& mod(int m)
    {
        coef.resize(m);
        return *this;
    }

    Polynom pow(int deg) const
    {
        Polynom res(0);
        res[0] = 1;
        for (int i = 1; i <= deg; i++)
        {
            res = res * (*this);
        }
        return res;
    }

    Polynom composition(const Polynom& other) const
    {
        Polynom res(MAGIC);
        res[0] = coef[0];
        Polynom b(0); b[0] = 1;
        for (int i = 1; i < MAGIC; i++)
        {
            b = b * other;
            b.mod(MAGIC);
            for (int j = 0; j < b->size(); j++)
            {
                res[j] = ((res[j] + (coef[i] * b[j]) % MOD) % MOD + MOD) % MOD;
            }
        }
        return res;
    }

    Polynom reversed() const
    {
        const std::size_t DEGREE = 999;
        Polynom res(DEGREE);
        res[0] = 1 / coef[0];
        for (int k = 1; k <= DEGREE; k++)
        {
            type_t sum = 0;
            for (int i = 1; i <= k; i++)
            {
                sum += (((i < coef.size()) ? coef[i] : 0) * res[k - i]) % MOD;
                sum = ((sum % MOD) + MOD) % MOD;
            }
            res[k] = ((-sum / coef[0]) % MOD + MOD) % MOD;
        }
        return res;
    }

    Polynom operator/(const Polynom& denominator) const
    {
        Polynom res = (*this) * denominator.reversed();
        res.mod(1000);
        return res;
    }

    type_t& operator[](const std::size_t& pos) const
    {
        return coef[pos];
    }

    std::vector<type_t>* operator->() const
    {
        return &coef;
    }

    std::size_t const degree() const
    {
        return coef.size() - 1;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p)
    {
        for (std::size_t i = 0; i < p->size(); i++)
        {
            os << p[i] << ' ';
        }
        return os;
    }
private:
    mutable std::vector <type_t> coef;
};

Polynom get_sqrt()
{
    std::vector <long long int> coef(MAGIC);
    for (int i = 0; i < coef.size(); i++)
    {
        coef[i] = choose(1, 2, i, Polynom::MOD);
    }
    return Polynom(std::move(coef));
}

Polynom get_log()
{
    std::vector<long long int> coef(MAGIC, 0);
    for (int i = 1; i < coef.size(); i++)
    {
        coef[i] = frac_by_mod(((i + 1) % 2) ? -1 : 1, i, Polynom::MOD);
    }
    return Polynom(std::move(coef));
}

Polynom get_exp()
{
    std::vector<long long int> coef(MAGIC, 0);
    for (int i = 0; i < coef.size(); i++)
    {
        coef[i] = frac_by_mod(1, factorial(i, Polynom::MOD), Polynom::MOD);
    }
    return Polynom(std::move(coef));
}

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    n++;
    vector <long long int> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    const Polynom pol(std::move(p));
    cout << get_sqrt().composition(pol).mod(m) << '\n';
    cout << get_exp().composition(pol).mod(m) << '\n';
    cout << get_log().composition(pol).mod(m) << '\n';

    return 0;
}