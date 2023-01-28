#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

size_t HammingDist(const string& s1, const string& s2)
{
    if (s1.size() != s2.size())
    {
        throw new exception();
    }
    size_t cnt = 0;
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
            cnt++;
    }

    return cnt;
}

size_t dPatternText(const string& pat, const string& text)
{
    size_t answ = 1e9;
    const size_t k = pat.size();
    for (int i = 0; i < text.size() - k; i++)
    {
        const string pat_dash = text.substr(i, k);
        answ = min(answ, HammingDist(pat, pat_dash));
    }

    return answ;
}

size_t dPatternDna(const string& pat, const vector<string>& dnas)
{
    size_t sum = 0;
    for (const string& dna : dnas)
    {
        sum += dPatternText(pat, dna);
    }
    return sum;
}

int main()
{
    int k; cin >> k;
    string text;
    vector<string> dnas;
    while (cin >> text)
    {
        if (text == "break")
            break;
        dnas.push_back(text);
    }

    unordered_set<string> used;
    size_t answ = 1e9;
    string answ_string = "";
    for (const string& dna : dnas)
    {
        for (int i = 0; i < dna.size() - k; i++)
        {
            const string pat = dna.substr(i, k);
            if (!used.count(pat))
            {
                used.insert(pat);
                size_t res = dPatternDna(pat, dnas);
                if (res < answ)
                {
                    answ = res;
                    answ_string = pat;
                }
            }
        }
    }
    cout << answ_string;
}
