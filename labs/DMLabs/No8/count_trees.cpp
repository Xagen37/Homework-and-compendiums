#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    const long long int MOD = 1000000007;
    int k, m; cin >> k >> m;
    vector <long long int> weights(k);
    for (int i = 0; i < k; i++)
    {
        cin >> weights[i];
    }

    vector <long long int> dp(m + 1, 0);
    dp[0] = 1;
    for (long long w : weights)
    { dp[w] = 1; }
    vector <long long int> possible(m + 1, 0);
    possible[0] = 1;

    for (int i = 1; i <= m; i++)
    {
        for (long long int w : weights)
        {
            if (w < i)
                dp[i] = (dp[i] + possible[i - w]) % MOD;
        }
        for (int left_w = 0; left_w <= i; left_w++)
        {
            possible[i] = (possible[i] + (dp[left_w] * dp[i - left_w]) % MOD) % MOD;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        cout << dp[i] % MOD << ' ';
    }
    return 0;
}