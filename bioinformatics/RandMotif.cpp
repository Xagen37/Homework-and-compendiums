#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using profile_t = unordered_map<char, vector<double>>;

profile_t gen_profile(const vector<string>& motifs)
{
    profile_t profile;
    const size_t len = motifs[0].size();
    for (int i = 0; i < len; i++)
    {
        int cntA = 0, cntC = 0, cntG = 0, cntT = 0;
        for (int k = 0; k < motifs.size(); k++)
        {
            switch (motifs[k][i])
            {
                case 'A': cntA++; break;
                case 'C': cntC++; break;
                case 'G': cntG++; break;
                case 'T': cntT++; break;
            }
        }
        size_t pseudo = motifs.size() + 4;
        profile['A'].push_back(static_cast<double>(cntA + 1) / pseudo);
        profile['C'].push_back(static_cast<double>(cntC + 1) / pseudo);
        profile['G'].push_back(static_cast<double>(cntG + 1) / pseudo);
        profile['T'].push_back(static_cast<double>(cntT + 1) / pseudo);
    }
    return profile;
}

double count_prob(profile_t& profile, const string& pat)
{
    double cnt = 1.0;
    for (int i = 0; i < pat.size(); i++)
    {
        cnt *= profile[pat[i]][i];
    }
    return cnt;
}

vector<string> get_motifs(const vector<string>& dnas, profile_t& profile, int k)
{
    vector<string> motifs(dnas.size());
    vector<double> maxs(dnas.size(), -1);
    for (int i = 0; i < dnas.size(); i++)
    {
        for (int z = 0; z < dnas[i].size() - k; z++)
        {
            string pat = dnas[i].substr(z, k);
            double res = count_prob(profile, pat);
            if (res > maxs[i])
            {
                maxs[i] = res;
                motifs[i] = pat;
            }
        }
    }
    return motifs;
}

size_t get_score(const vector<string>& motifs)
{
    size_t score = 0;
    const vector<char> labels = { 'A', 'C', 'G', 'T' };
    for (int i = 0; i < motifs[0].size(); i++)
    {
        vector<int> cnts(4);
        for (int z = 0; z < motifs.size(); z++)
        {
            switch (motifs[z][i])
            {
                case 'A': cnts[0]++; break;
                case 'C': cnts[1]++; break;
                case 'G': cnts[2]++; break;
                case 'T': cnts[3]++; break;
            }
        }

        int max_cnt = -1;
        char most_freq;
        for (int i = 0; i < 4; i++)
        {
            if (cnts[i] > max_cnt || max_cnt == -1)
            {
                max_cnt = cnts[i];
                most_freq = labels[i];
            }
        }

        for (int z = 0; z < motifs.size(); z++)
        {
            if (motifs[z][i] != most_freq)
            {
                score++;
            }
        }
    }

    return score;
}

vector<string> randMotifSearch(const vector<string>& dnas, int k, int t)
{
    const int len = dnas[0].size();
    vector<string> best_motifs;
    for (int i = 0; i < dnas.size(); i++)
    {
        best_motifs.push_back(dnas[i].substr(rand() % (len - k + 1), k));
    }

    size_t min_score = get_score(best_motifs);

    while (true)
    {
        profile_t profile = gen_profile(best_motifs);
        vector<string> motifs = get_motifs(dnas, profile, k);
        size_t score = get_score(motifs);

        if (score < min_score)
        {
            min_score = score;
            best_motifs = motifs;
        }
        else
        {
            return best_motifs;
        }
    }
}

int main()
{
    srand(time(0));

    int k, t; cin >> k >> t;
    vector<string> dnas;
    string text;
    while (cin >> text)
    {
        if (text == "break")
            break;

        dnas.push_back(text);
    }

    vector<string> best_motifs = randMotifSearch(dnas, k, t);
    size_t min_score = get_score(best_motifs);

    for (int i = 1; i < 1000; i++)
    {
        vector<string> motifs = randMotifSearch(dnas, k, t);
        size_t score = get_score(motifs);

        if (score < min_score)
        {
            min_score = score;
            best_motifs = motifs;
        }
    }

    for (const string& motif : best_motifs)
    {
        cout << motif << '\n';
    }

    return 0;
}