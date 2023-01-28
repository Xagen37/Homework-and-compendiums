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
    string os; cin >> os;

    string garbage; cin >> garbage >> ws; // "----" delimiter and line break

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

//----------------------------------------------------------------------------

    vector<vector<double>> viterbi(states.size(), vector<double>(os.size(), -1));
    vector<vector<int>> mem(states.size(), vector<int>(os.size(), -1));
    for (int state = 0; state < states.size(); state++)
    {
        int pos = alphabet.find(os[0]);
        viterbi[state][0] = emissions[state][pos];
    }

    for (int t = 1; t < os.size(); t++)
    {
        int pos = alphabet.find(os[t]);
        for (int state = 0; state < states.size(); state++)
        {
            for (int prev = 0; prev < states.size(); prev++)
            {
                double curr = viterbi[prev][t - 1] * transitions[prev][state] * emissions[state][pos];
                if (curr > viterbi[state][t])
                {
                    viterbi[state][t] = curr;
                    mem[state][t] = prev;
                }
            }
        }
    }

    double max_p = -1;
    int max_state = -1;
    for (int state = 0; state < states.size(); state++)
    {
        if (viterbi[state].back() > max_p)
        {
            max_p = viterbi[state].back();
            max_state = state;
        }
    }

    int t = os.size() - 1;
    int curr_state = max_state;
    string answ;
    while (t >= 0 && curr_state != -1)
    {
        answ.push_back(states[curr_state]);
        curr_state = mem[curr_state][t];
        t--;
    }

    reverse(answ.begin(), answ.end());
    cout << answ;
//-------------------------------------------------------------------------

    //vector<vector<double>> alphas(states.size(), vector<double>(os.size()));
    //for (int state = 0; state < states.size(); state++)
    //{
    //    int pos = alphabet.find(os[0]);
    //    alphas[state][0] = emissions[state][pos];
    //}

    //for (int i = 1; i < os.size(); i++)
    //{
    //    int pos = alphabet.find(os[i]);
    //    for (int state = 0; state < states.size(); state++)
    //    {
    //        double sum = 0.0;
    //        for (int j = 0; j < states.size(); j++)
    //        {
    //            sum += alphas[j][i - 1] * transitions[j][state];
    //        }
    //        alphas[state][i] = sum * emissions[state][pos];
    //    }
    //}

    //vector<vector<double>> betas(states.size(), vector<double>(os.size()));
    //for (int state = 0; state < states.size(); state++)
    //{
    //    betas[state].back() = 1;
    //}

    //for (int i = os.size() - 1; i > 0; i--)
    //{
    //    int pos = alphabet.find(os[i]);
    //    for (int state = 0; state < states.size(); state++)
    //    {
    //        double sum = 0.0;
    //        for (int j = 0; j < states.size(); j++)
    //        {
    //            sum += betas[j][i] * transitions[state][j] * emissions[j][pos];
    //        }
    //        betas[state][i - 1] = sum;
    //    }
    //}

    //double norm = 0.0;
    //for (int state = 0; state < states.size(); state++)
    //{
    //    norm += alphas[state].back() * betas[state].back();
    //}

    //for (int i = 0; i < os.size(); i++)
    //{
    //    double max = -1;
    //    char max_state = '!';
    //    for (int state = 0; state < states.size(); state++)
    //    {
    //        double curr = alphas[state][i] * betas[state][i] / norm;
    //        if (curr > max)
    //        {
    //            max = curr;
    //            max_state = states[state];
    //        }
    //    }
    //    cout << max_state;
    //}
    return 0;
}
