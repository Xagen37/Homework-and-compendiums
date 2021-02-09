#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
const int MAX = 20000 * 20000 + 1;
double dist(pair<int, int> & p1, pair <int, int> & p2)
{
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
    vector <bool> us(n, false);
    vector <pair <int, int> > point(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        point[i] = {a, b};
    }
 
    vector <double> min_e(n, MAX);
    vector <int> s;
    s.push_back(0);
    min_e[0] = 0;
    us[0] = 1;
    for (int i = 1; i < n; i++)
    {
        min_e[i] = min(min_e[i], dist(point[0], point[i]));
    }
 
    double answ = 0;
    while(s.size() < n)
    {
        double min_w = MAX;
        int id = 0;
        for (int i = 0; i < n; i++)
        {
            if (!us[i])
            {
                if (min_e[i] < min_w)
                {
                    min_w = min_e[i];
                    id = i;
                }
            }
        }
        s.push_back(id);
        us[id] = 1;
        answ += min_w;
        for (int i = 0; i < n; i++)
        {
            if (i != id)
            {
                min_e[i] = min(min_e[i], dist(point[i], point[id]));
            }
        }
    }
 
    cout.precision(20);
    cout << answ;
    return 0;
}