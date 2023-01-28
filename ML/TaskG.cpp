#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int count_ones(int arg)
{
    int cnt = 0;
    while (arg > 0)
    {
        if (arg & 1)
            cnt++;
        arg >>= 1;
    }
    return cnt;
}

int main()
{
    int m; cin >> m;
    int n = 1 << m;

    vector<int> func(n);
    int truth_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> func[i];
        if (func[i])
            truth_cnt++;
    }

    if (!truth_cnt)
    {
        cout << 1 << '\n' << 1 << '\n';
        for (int bit = 0; bit <= m; bit++)
        {
            cout << -1.0 << ' ';
        }
        return 0;
    }

    if (truth_cnt > 512)
        truth_cnt = 512;

    cout << 2 << '\n';
    cout << truth_cnt << ' ' << 1 << '\n';
    for (int i = 0, copy = 0; i < func.size() && copy < truth_cnt; i++, copy++)
    {
        if (!func[i])
        {
            copy--;
            continue;
        }
        for (int bit = 0; bit < m; bit++)
        {
            if (i & (1 << bit))
            {
                cout << 1.0 << ' ';
            }
            else
            {
                cout << -1.0 << ' ';
            }
        }
        cout << 0.5 - count_ones(i) << '\n';
    }

    for (int i = 0; i < truth_cnt; i++)
    {
        cout << 1 << ' ';
    }
    cout << -0.5;

    return 0;
}