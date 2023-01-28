#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// Precision = TP / (TP + FP)
// Recall = TP / (TP + FN)
// F = 2 * Precision * Recall / (Precision + Recall)
double precision(double tp, double fp)
{
    return tp + fp == 0 ? 0 : tp / (tp + fp);
}

double recall(double tp, double fn)
{
    return tp + fn == 0 ? 0 : tp / (tp + fn);
}

double f_measure(double prec, double rec)
{
    return prec + rec == 0 ? 0 : 2.0 * prec * rec / (prec + rec);
}


int main()
{
    int k; cin >> k;
    vector<vector<int>> cm(k, vector<int>(k));
    int all = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> cm[i][j];
            all += cm[i][j];
        }
    }

    vector<int> fps_cnt(k);
    vector<int> fns_cnt(k);
    vector<int> tps_cnt(k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i == j)
                continue;

            fns_cnt[i] += cm[i][j];
            fps_cnt[i] += cm[j][i];
        }
        tps_cnt[i] = cm[i][i];
    }

    vector<int> micro_tps(k);
    vector<int> micro_fps(k);
    vector<int> micro_fns(k);

    for (int i = 0; i < k; i++)
    {
        int all_class = fns_cnt[i] + tps_cnt[i];
        micro_tps[i] = tps_cnt[i] * all_class;
        micro_fps[i] = fps_cnt[i] * all_class;
        micro_fns[i] = fns_cnt[i] * all_class;
    }

    double micro_tp = accumulate(micro_tps.begin(), micro_tps.end(), 0) / static_cast<double>(all);
    double micro_fp = accumulate(micro_fps.begin(), micro_fps.end(), 0) / static_cast<double>(all);
    double micro_fn = accumulate(micro_fns.begin(), micro_fns.end(), 0) / static_cast<double>(all);

    double micro_prec = precision(micro_tp, micro_fp);
    double micro_rec = recall(micro_tp, micro_fn);

    double micro_f = f_measure(micro_prec, micro_rec);

    vector<double> macro_precs(k);
    vector<double> macro_recs(k);

    for (int i = 0; i < k; i++)
    {
        int all_class = fns_cnt[i] + tps_cnt[i];
        macro_precs[i] = precision(tps_cnt[i], fps_cnt[i]) * all_class;
        macro_recs[i] = recall(tps_cnt[i], fns_cnt[i]) * all_class;
    }

    double macro_prec = accumulate(macro_precs.begin(), macro_precs.end(), 0.0) / all;
    double macro_rec = accumulate(macro_recs.begin(), macro_recs.end(), 0.0) / all;

    double macro_f = f_measure(macro_prec, macro_rec);

    vector<double> fs(k);

    for (int i = 0; i < k; i++)
    {
        int all_class = fns_cnt[i] + tps_cnt[i];
        double prec = precision(tps_cnt[i], fps_cnt[i]);
        double rec = recall(tps_cnt[i], fns_cnt[i]);
        fs[i] = f_measure(prec, rec) * all_class;
    }

    double f = accumulate(fs.begin(), fs.end(), 0.0) / all;

    cout << setprecision(20);
    cout << micro_f << '\n' << macro_f << '\n' << f;
    return 0;
}