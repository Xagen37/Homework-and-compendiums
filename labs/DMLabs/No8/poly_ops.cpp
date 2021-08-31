#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Polynom
{
    constexpr static long long int MOD = 998244353;

    using type_t = long long int;

    Polynom(std::size_t degree)
        : coef(degree + 1)
    {}

    Polynom(std::vector<type_t>&& other)
        : coef(std::move(other))
    {}

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
        res->resize(1000);
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

using namespace std;

int main()
{
    int n, m; 
    cin >> n >> m;
    n++; m++;
    vector <long long int> vector_p(n), vector_q(m);
    for (int i = 0; i < n; i++)
        cin >> vector_p[i];
    for (int i = 0; i < m; i++)
        cin >> vector_q[i];

    Polynom p(std::move(vector_p));
    Polynom q(std::move(vector_q));

    Polynom sum = p + q, mult = p * q, div = p / q;
    cout << sum.degree() << '\n' << sum << '\n';
    cout << mult.degree() << '\n' << p * q << '\n';
    cout << p / q;

    return 0;
}