#include <algorithm>
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// In the task elements of Galois field can be viewed as bitmasks
using Alpha = uint32_t;

int m;  // m from `n = 2^m - 1`
uint64_t prim_poly; // Primitive polynomial for Galois field.
mt19937 rgen(random_device{}());
uniform_real_distribution<> dis(0.0, 1.0);

vector<Alpha> alphas;  // values of elements of Galois field
vector<Alpha> reverse_alphas;  // precalculated inverse elements
vector<vector<Alpha>> mul_table;  // precalculated multiplication table

// Multiplication in Galois field modulo given primitive polynomial.
// See also: https://en.wikipedia.org/wiki/Finite_field_arithmetic
Alpha alpha_mul(Alpha a, Alpha b)
{
    Alpha res = 0;
    while (a && b)
    {
        if (b & 1)
        {
            res ^= a;
        }

        if (a & (1 << (m - 1)))
        {
            a <<= 1;
            a ^= prim_poly;
        }
        else
        {
            a <<= 1;
        }
        b >>= 1;
    }
    return res;
}

// General structure for polynomials with helper methods.
// Polynomial is a vector of alphas, where i-th alpha
// is a coefficient at x^i.
struct Polynom
{
    vector<Alpha> poly;

    // Standard polynomial multiplication
    friend Polynom operator*(const Polynom& lhs, const Polynom& rhs)
    {
        Polynom res;
        res.poly.resize(lhs.poly.size() - 1 + rhs.poly.size() - 1 + 1);
        for (int l = 0; l < lhs.poly.size(); l++)
        {
            Alpha curr_l = lhs[l];
            if (curr_l)
            {
                for (int r = 0; r < rhs.poly.size(); r++)
                {
                    int deg = l + r;
                    Alpha coef = mul_table[curr_l][rhs.poly[r]];
                    res[deg] ^= coef;
                }
            }
        }
        return res;
    }

    // Modulo operation for polynomials.
    // lhs - dividend, rhs - divisor (returns lhs % rhs)
    friend Polynom remainder(const Polynom& lhs, const Polynom& rhs)
    {
        Polynom temp = lhs;
        int l_deg = temp.poly.size() - 1;
        const int r_deg = rhs.poly.size() - 1;
        for (int i = l_deg; i >= 0; i--)
        {
            if (temp.poly[i])
            {
                break;
            }
            else
            {
                l_deg--;
                temp.poly.pop_back();
            }
        }
        while (l_deg >= r_deg)
        {
            int deg_diff = l_deg - r_deg;
            for (int i = r_deg; i >= 0; i--)
            {
                temp[i + deg_diff] ^= rhs[i];
            }
            for (int i = l_deg; i >= 0; i--)
            {
                if (temp[i])
                {
                    break;
                }
                else
                {
                    l_deg--;
                    temp.poly.pop_back();
                }
            }
        }
        return temp;
    }

    Polynom& operator+=(const Polynom& rhs)
    {
        int max_size = this->poly.size() > rhs.poly.size() ? this->poly.size() : rhs.poly.size();
        poly.resize(max_size);
        for (int i = rhs.poly.size() - 1; i >= 0; i--)
        {
            poly[i] ^= rhs[i];
        }
        return *this;
    }

    Alpha& operator[](size_t i)
    { return poly[i]; }

    const Alpha& operator[](size_t i) const
    { return poly[i]; }

    // Multiplies every coefficient by given value.
    void mul_by_alpha(const Alpha& val)
    {
        for (Alpha& alpha : poly)
        {
            alpha = mul_table[alpha][val];
        }
    }
};

// Declarations of polynomials, that are used further.
Polynom betha;     // B(x) from Berlekamp-Massey algorithm.
Polynom decode;    // Polynom for Decode result.
Polynom encode;    // Polynom for Encode result.
Polynom generator; // Generator polynomial for BCH code.
Polynom info;      // Input for Encode.
Polynom lambda;    // Error location polynomial from Berlekamp-Massey algorithm.
Polynom syndrom;   // Syndrome polynomial
Polynom word;      // Input for Decode.

// Calculate elements in Galois field with given primitive polynomial.
void count_alphas()
{
    alphas.resize((1U << m) - 1);
    reverse_alphas.resize(alphas.size() + 1);
    mul_table.resize(reverse_alphas.size(), vector<Alpha>(reverse_alphas.size(), 0));

    alphas[0] = 1U;
    for (int i = 1; i < alphas.size(); i++)
    {
        // a^i = (a^(i - 1) * x) % p, where p is primitive polynomial
        alphas[i] = alpha_mul(alphas[i - 1], 0b10);
    }

    // Precalculate multiplication matrix for alphas
    for (int i = 0; i < reverse_alphas.size(); i++)
    {
        mul_table[0][i] = mul_table[i][0] = 0;
    }
    for (Alpha i = 1; i < mul_table.size(); i++)
    {
        for (Alpha j = i; j < mul_table.size(); j++)
        {
            mul_table[i][j] = mul_table[j][i] = alpha_mul(i, j);
        }
    }

    // Precalculate inverse elements for alphas
    reverse_alphas[1] = 1U;
    for (int i = 1; i < alphas.size(); i++)
    {
        Alpha reverse_alpha = alphas[i];
        for (int j = 1; j < alphas.size(); j++)
        {
            if (mul_table[reverse_alpha][alphas[j]] == 1)
            {
                reverse_alphas[reverse_alpha] = alphas[j];
                continue;
            }
        }
    }
}

// Build cyclotomic class, starting from element val.
vector<int> build_cyclo(int val, unordered_set<int>& used)
{
    vector<int> cyclo;
    int start = val;
    do
    {
        used.insert(val);
        cyclo.push_back(val);
        val = (val * 2) % ((1 << m) - 1);
    } while (start != val);
    return cyclo;
}

// Generator polynom for bch code is LCM of minimal polynomials.
// As here we exist in binary arithmetics, x - y == x + y
void build_generator(Polynom& generator, int d)
{
    unordered_set<int> used;
    for (int b = 1; b <= 1 + d - 2; b++)
    {
        if (!used.count(b))
        {
            auto cyclo = build_cyclo(b, used);
            for (int deg : cyclo)
            {
                Polynom temp;
                temp.poly = { alphas[deg], 1 };
                generator = generator * temp;
            }
        }
    }
}

void print_poly(const Polynom& poly)
{
    for (auto coef : poly.poly)
    {
        cout << coef << ' ';
    }
    cout << '\n';
}

// Encode given info vector with systematic bch code.
// c(x) = x^r * a(x) - x^r * a(x) % g(x),
// where r = n - k, a(x) - info polynomial, g(x) - generator polynomial.
void Encode(int r, int n)
{
    fill(encode.poly.begin(), encode.poly.end(), 0);
    for (int i = r; i < n; i++)
    {
        encode[i] = info[i - r];
    }

    encode += remainder(encode, generator);
}

// Fix errors for given code word with Berlekamp-Massey algorithm.
void Decode(int d)
{
    // Calculate syndrome polynomial with Horner's method.
    bool not_null = false;
    for (int i = 1; i < d; i++)
    {
        const Alpha curr = alphas[i];
        Alpha sum = word.poly.back();

        for (int j = word.poly.size() - 2; j >= 0; j--)
        {
            sum = mul_table[sum][curr];
            sum ^= word[j];
        }

        syndrom[i] = sum;
        if (sum)
        {
            not_null = true;
        }
    }
    cout << "Syndrom: ";
    print_poly(syndrom);

    // If syndrome polynomial is zero, then no errors were detected.
    if (!not_null)
    {
        return;
    }

    // Initialization for BM algorithm.
    lambda.poly.resize(1);
    lambda[0] = 1;
    betha.poly.resize(1);
    betha[0] = 1;
    int L = 0; // L is the current number of assumed errors

    for (int i = 1; i < d; i++)
    {
        cout << "Before\n";
        cout << "i = " << i << ", L = " << L << endl;
        cout << "B(x) = ";
        print_poly(betha);
        cout << "/\\(x) = ";
        print_poly(lambda);

        betha.poly.resize(betha.poly.size() + 1);
        for (int j = betha.poly.size() - 1; j > 0; j--)
        {
            betha[j] = betha[j - 1];
        }
        betha[0] = 0;

        // As we are in binary field and are working with BCH code in narrow sense,
        // discrepancy for even iterations is anyway zero, no need to calculate it
        if (i % 2)
        {
            // Calculate discrepancy
            Alpha delta = 0;
            for (int j = 0; j <= L; j++)
            {
                delta ^= mul_table[lambda[j]][syndrom[i - j]];
            }
            cout << "Delta = " << delta << endl;;
            if (!delta)
            {
                continue;
            }

            Polynom theta = betha;
            theta.mul_by_alpha(delta);
            theta += lambda;

            if (2 * L <= i - 1)
            {
                lambda.mul_by_alpha(reverse_alphas[delta]);
                swap(betha.poly, lambda.poly);
                L = i - L;
            }
            swap(lambda.poly, theta.poly);
        }
        cout << "After\n";
        cout << "i = " << i << ", L = " << L << endl;
        cout << "B(x) = ";
        print_poly(betha);
        cout << "/\\(x) = ";
        print_poly(lambda);
    }

    // Calculate degree of locator polynomial lambda.
    int deg = lambda.poly.size() - 1;
    for (; deg > 0; deg--)
    {
        if (lambda[deg])
        {
            break;
        }
    }

    // If lambda's degree != L, then number of errors is more than (d - 1) / 2
    // And so the word can not be corrected
    if (deg != L)
    {
        return;
    }

    // Correct errors in places, pointed by error locator polynomial.
    // To find such places, we need to find roots of the polynomial,
    // which can be done by brute force.
    for (int i = 0; i < word.poly.size(); i++)
    {
        Alpha curr = reverse_alphas[alphas[i]];
        Alpha sum = lambda.poly.back();

        for (int j = lambda.poly.size() - 2; j >= 0; j--)
        {
            sum = mul_table[sum][curr];
            sum ^= lambda[j];
        }

        if (sum == 0)
        {
            word[i] ^= 1;
        }
    }
}

double Simulate(const double prob, const int iter_num, const int max_err,
                int r, int n, int d)
{
    int it_cnt = 1, err_cnt = 0;
    for (; it_cnt <= iter_num; it_cnt++)
    {
        for (int i = 0; i < info.poly.size(); i++)
        {
            info[i] = rgen() % 2;
        }

        Encode(r, n);
        
        for (int i = 0; i < encode.poly.size(); i++)
        {
            word[i] = encode[i];
            if (dis(rgen) <= prob)
            {
                word[i] ^= 1;
            }
        }

        Decode(d);

        bool ok = true;
        for (int i = 0; i < encode.poly.size(); i++)
        {
            if (encode[i] != word[i])
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            err_cnt++;
            if (err_cnt >= max_err)
            {
                break;
            }
        }
    }
    return static_cast<double>(err_cnt) / it_cnt;
}



int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    m = 1;
    int copy_n = n;
    while (copy_n >>= 1)
    {
        m++;
    }

    // As primitive polynom is not so big and is used only for operations with alphas,
    // it will be more convenient to view it as a bitmask.
    cin >> prim_poly;

    count_alphas();

    int d; cin >> d;

    generator.poly = { 1 };
    build_generator(generator, d);

    int k = n - generator.poly.size() + 1;
    cout << k << '\n';
    print_poly(generator);

    const int r = n - k;
    string command;
    info.poly.resize(k);
    decode.poly.resize(k);
    word.poly.resize(n);
    encode.poly.resize(n);
    lambda.poly.resize(1);
    betha.poly.resize(1);
    syndrom.poly.resize(d);
    while (cin >> command)
    {
        if (command == "Encode")
        {
            for (int i = 0; i < k; i++)
            {
                cin >> info.poly[i];
            }

            Encode(r, n);
            print_poly(encode);
            continue;
        }
        if (command == "Decode")
        {
            for (int i = 0; i < n; i++)
            {
                cin >> word[i];
            }

            Decode(d);
            print_poly(word);
            continue;
        }
        if (command == "Simulate")
        {
            double prob;
            int iter_num, max_err;
            cin >> prob >> iter_num >> max_err;
            cout << Simulate(prob, iter_num, max_err, r, n, d) << '\n';
            continue;
        }
        cout << "FAILURE\n";
    }
}
