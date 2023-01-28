#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string get_and_parse()
{
    string res;
    string collect;
    getline(cin, collect);
    for (size_t i = 0; i < collect.size(); i++)
    {
        if (!isspace(collect[i]))
        {
            res.push_back(collect[i]);
        }
    }
    return res;
}

int main()
{
    int it_num; cin >> it_num;

    string garbage; cin >> garbage; // "----" delimiter

    string os; cin >> os >> ws;

    cin >> garbage >> ws; // "----" delimiter and line break

    const string alphabet = get_and_parse();

    cin >> garbage >> ws; // "----" delimiter and line break

    const string states = get_and_parse();

    cin >> garbage >> ws; // "----" delimiter and line break
    getline(cin, garbage); // column names;

    vector<vector<double>> transitions(states.size(), vector<double>(states.size()));
    for (size_t i = 0; i < states.size(); i++)
    {
        string probs; getline(cin, probs);
        istringstream in(probs);
        char c; in >> c; // row name
        for (size_t j = 0; j < states.size(); j++)
        {
            in >> transitions[i][j];
        }
    }

    cin >> garbage >> ws; // "----" delimiter and line break
    getline(cin, garbage); // column names;

    vector<vector<double>> emissions(states.size(), vector<double>(alphabet.size()));
    for (size_t i = 0; i < states.size(); i++)
    {
        string probs; getline(cin, probs);
        istringstream in(probs);
        char c; in >> c; // row name
        for (size_t j = 0; j < alphabet.size(); j++)
        {
            in >> emissions[i][j];
        }
    }

//--------------------------------------------------------
    for (int iteration = 0; iteration < it_num; iteration++)
    {
        vector<vector<double>> alphas(states.size(), vector<double>(os.size()));
        for (int state = 0; state < states.size(); state++)
        {
            int pos = alphabet.find(os[0]);
            alphas[state][0] = emissions[state][pos];
        }

        for (int i = 1; i < os.size(); i++)
        {
            int pos = alphabet.find(os[i]);
            for (int state = 0; state < states.size(); state++)
            {
                double sum = 0.0;
                for (int j = 0; j < states.size(); j++)
                {
                    sum += alphas[j][i - 1] * transitions[j][state];
                }
                alphas[state][i] = sum * emissions[state][pos];
            }
        }

        vector<vector<double>> betas(states.size(), vector<double>(os.size()));
        for (int state = 0; state < states.size(); state++)
        {
            betas[state].back() = 1;
        }

        for (int i = os.size() - 1; i > 0; i--)
        {
            int pos = alphabet.find(os[i]);
            for (int state = 0; state < states.size(); state++)
            {
                double sum = 0.0;
                for (int j = 0; j < states.size(); j++)
                {
                    sum += betas[j][i] * transitions[state][j] * emissions[j][pos];
                }
                betas[state][i - 1] = sum;
            }
        }

        double norm = 0.0;
        for (int state = 0; state < states.size(); state++)
        {
            norm += alphas[state].back() * betas[state].back();
        }

        vector<vector<double>> gammas(states.size(), vector<double>(os.size()));

        for (int i = 0; i < os.size(); i++)
        {
            for (int state = 0; state < states.size(); state++)
            {
                gammas[state][i] = alphas[state][i] * betas[state][i] / norm;
            }
        }

        vector<vector<vector<double>>> xis(states.size(), vector<vector<double>>(states.size(), vector<double>(os.size())));
        for (int i = 0; i < os.size() - 1; i++)
        {
            double xi_norm = 0;
            int next_pos = alphabet.find(os[i + 1]);
            for (int state1 = 0; state1 < states.size(); state1++)
            {
                for (int state2 = 0; state2 < states.size(); state2++)
                {
                    xi_norm += alphas[state1][i] * transitions[state1][state2] * betas[state2][i + 1] * emissions[state2][next_pos];
                }
            }

            for (int state1 = 0; state1 < states.size(); state1++)
            {
                for (int state2 = 0; state2 < states.size(); state2++)
                {
                    xis[state1][state2][i] = alphas[state1][i] * transitions[state1][state2] * betas[state2][i + 1] * emissions[state2][next_pos];
                    xis[state1][state2][i] /= xi_norm;
                }
            }
        }

        for (int state1 = 0; state1 < states.size(); state1++)
        {
            for (int state2 = 0; state2 < states.size(); state2++)
            {
                double xi_sum = 0.0;
                double gamma_sum = 0.0;
                for (int i = 0; i < os.size() - 1; i++)
                {
                    xi_sum += xis[state1][state2][i];
                    gamma_sum += gammas[state1][i];
                }

                transitions[state1][state2] = xi_sum / gamma_sum;
            }
        }

        for (int state = 0; state < states.size(); state++)
        {
            for (int alph = 0; alph < alphabet.size(); alph++)
            {
                double gamma_sum = 0.0;
                double indic_sum = 0.0;
                for (int i = 0; i < os.size(); i++)
                {
                    if (alphabet[alph] == os[i])
                    {
                        indic_sum += gammas[state][i];
                    }
                    gamma_sum += gammas[state][i];
                }

                emissions[state][alph] = indic_sum / gamma_sum;
            }
        }
    }
//-------------------------------------------------------------------------

    cout << setprecision(3) << fixed;

    for (int state = 0; state < states.size(); state++)
    {
        cout << states[state] << " ";
    }
    cout << '\n';

    for (int state = 0; state < states.size(); state++)
    {
        cout << states[state] << " ";
        for (int state2 = 0; state2 < transitions[state].size(); state2++)
        {
            cout << transitions[state][state2] << " ";
        }
        cout << '\n';
    }

    cout << "--------" << '\n';

    for (int alph = 0; alph < alphabet.size(); alph++)
    {
        cout << alphabet[alph] << " ";
    }
    cout << '\n';

    for (int state = 0; state < states.size(); state++)
    {
        cout << states[state] << " ";
        for (int alph = 0; alph < emissions[state].size(); alph++)
        {
            cout << emissions[state][alph] << " ";
        }
        cout << '\n';
    }

    return 0;
}