#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Polynom
{
    constexpr static long long int MOD = 998244353;

    using type_t = long long int;

    Polynom() = default;

    Polynom(std::size_t degree) noexcept
        : coef(degree + 1, 0)
    {}

    Polynom(std::vector<type_t>&& other) noexcept
        : coef(std::move(other))
    {}

    Polynom(const Polynom& other) noexcept
        :coef(other.coef)
    {}

    Polynom(Polynom&& other) noexcept
        :coef(std::move(other.coef))
    {}

    Polynom& operator=(const Polynom& other)
    {
        this->coef = other.coef;
        return *this;
    }

    Polynom& operator=(Polynom&& other) noexcept
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
            res[pos] = other[pos] + coef[pos];
            //res[pos] = (other[pos] + coef[pos]) % MOD;
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
                res[i + j] += coef[i] * other[j];
                //res[i + j] += (coef[i] * other[j]) % MOD;
                //res[i + j] %= MOD;
            }
        }

        return res;
    }

    Polynom operator* (const long long int& mult) const
    {
        Polynom res(degree());
        for (long long int i = 0; i < coef.size(); i++)
        {
            res[i] = (coef[i] * mult);
            //res[i] = (coef[i] * mult) % MOD;
        }
        return res;
    }

    Polynom& mod(int m)
    {
        coef.resize(m);
        return *this;
    }

    Polynom& trim()
    {
        int n = coef.size() - 1;
        for (; n >= 0; n--)
        {
            if (coef[n]) break;
        }
        n++;
        coef.resize(n);
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
        const int MAGIC = 100;
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

long long int factorial(long long int n)
{
    long long int res = 1;
    for (int i = 1; i <= n; i++)
    {
        res = res * i;
    }
    return res;
}

using namespace std;

Polynom count_ui(long long int id, long long int k, long long int p_i)
{
    Polynom res(0); res[0] = 1LL;
    for (int i = k; i > 0; i--)
    {
        Polynom mult(1);
        mult[1] = 1LL; mult[0] = -id + i;
        res = res * mult;
        res.mod(k + 1);
    }
    return res * p_i;
}

long long int gcd (long long int x, long long int y)
{ return y ? gcd(y, x % y) : x; }

void gcd(Polynom& numer, vector <long long int>& denom)
{
    for (int i = 0; i < numer->size(); i++)
    {
        long long int x = abs(numer[i]);
        long long int g;
        while ((g = gcd(x, denom[i])) != 1)
        {
            x /= g;
            denom[i] /= g;
        }
        numer[i] = (numer[i] >= 0) ? x : -x;
    }
}

void simplify_and_print(long long int numerator, long long int denominator)
{
    long long int x = abs(numerator);
    long long int g;
    while ((g = gcd(x, denominator)) != 1)
    {
        x /= g;
        denominator /= g;
    }
    cout << ((numerator >= 0) ? x : -x) << '/' << denominator << ' ';
}

int main()
{
    long long int r, k; cin >> r >> k;
    Polynom in(k);
    for (long long int i = 0; i <= k; i++)
    {
        cin >> in[i];
    }
    in.trim();
    Polynom answ_numerator(0);
    vector <long long int> answ_denominator(k + 1, factorial(k));
    
    for (long long int i = 0; i <= in.degree() /*m*/; i++)
    {
        Polynom ui = count_ui(i, k, in[i]);
        ui = ui * pow(r, in.degree() - i);
        answ_numerator = answ_numerator + ui;
    }
    answ_numerator.mod(k + 1);

    gcd(answ_numerator, answ_denominator);
    for (int i = 1; i <= in.degree(); i++)
    {
        for (int j = 0; j < answ_denominator.size(); j++)
        {
            answ_denominator[j] *= r;
        }
        gcd(answ_numerator, answ_denominator);
    }

    for (long long int i = 0; i <= answ_numerator.degree(); i++)
    {
        simplify_and_print(answ_numerator[i], answ_denominator[i]);
    }
    return 0;
}