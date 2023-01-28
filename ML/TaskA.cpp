#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> parts(k);
    vector<vector<int>> cnts(m);
    
    for (int i = 1; i <= n; i++)
    {
        int obj; cin >> obj; obj--;
        cnts[obj].push_back(i);
    }

    int it = 0;
    for (const vector<int>& clazz : cnts)
    {
        for (const int& elem : clazz)
        {
            parts[it].push_back(elem);
            it = (it + 1) % k;
        }
    }

    for (const vector<int>& part : parts)
    {
        cout << part.size();
        for (const int& elem : part)
        {
            cout << ' ' << elem;
        }
        cout << '\n';
    }

    return 0;
}