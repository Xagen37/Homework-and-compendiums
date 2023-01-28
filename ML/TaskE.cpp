#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    constexpr long double EDINITSA = 1.0;

    long long int k; cin >> k;

    vector<long long int> lambdas(k);
    for (int i = 0; i < k; i++)
    {
        cin >> lambdas[i];
    }

    long long int alpha; cin >> alpha;

    long long int n; cin >> n;

    vector<long long int> msg_in_classes_freq(k);
    vector<unordered_map<string, long long int>> words_in_classes_freq(k);
    unordered_set<string> unique_words;

    for (int i = 0; i < n; i++)
    {
        long long int c; cin >> c; c--;
        long long int l; cin >> l;
        msg_in_classes_freq[c]++;
        unordered_set<string> fit_words;
        for (int z = 0; z < l; z++)
        {
            string word; cin >> word;
            fit_words.insert(std::move(word));
        }

        for (const string& word : fit_words)
        {
            words_in_classes_freq[c][word]++;
            unique_words.insert(word);
        }
    }

    cout << setprecision(20);

    long long int m; cin >> m;
    for (int i = 0; i < m; i++)
    {
        long long int l; cin >> l;
        vector<string> test(l);
        unordered_set<string> in_test;
        vector<long double> classify(k);
        for (int z = 0; z < l; z++)
        {
            cin >> test[z];
            in_test.insert(test[z]);
        }

        for (int clazz = 0; clazz < k; clazz++)
        {
            long double sum_log = log(static_cast<double>(lambdas[clazz])) + log(static_cast<double>(msg_in_classes_freq[clazz])) - log(static_cast<double>(n));

            for (const string& word : unique_words)
            {
                const long double nominator = words_in_classes_freq[clazz][word] + alpha;
                const long double denominator = 2 * alpha + msg_in_classes_freq[clazz];
                const long double div = nominator / denominator;
                sum_log += log(in_test.count(word) ? div : EDINITSA - div);
            }

            classify[clazz] = sum_log;
        }

        long double adjustment = *max_element(classify.begin(), classify.end());
        long double denominator = 0.0;
        for (int mem = 0; mem < classify.size(); mem++)
        {
            classify[mem] -= adjustment;
            denominator += classify[mem] = exp(classify[mem]);
        }

        for (int clazz = 0; clazz < k; clazz++)
        {
            cout << classify[clazz] / denominator << ' ';
        }

        /*for (int clazz = 0; clazz < k; clazz++)
        {
            long double denom_sum = EDINITSA;
            for (int other = 0; other < k; other++)
            {
                if (other == clazz)
                    continue;

                denom_sum += exp(classify[other] - classify[clazz]);
            }

            cout << EDINITSA / denom_sum << ' ';
        }*/

        cout << '\n';
    }

    return 0;
}