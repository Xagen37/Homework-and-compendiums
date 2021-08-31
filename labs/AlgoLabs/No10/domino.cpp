#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
 
using namespace std;
#define ENTRY pair<long long int, long long int>
 
struct Hasher
{
    unsigned int operator()(const ENTRY& e) const noexcept
    {
        return ((e.first * 239) % 1000000007 + e.second) % 1000000007;
    }
};
 
vector <ENTRY> left_part;
unordered_set<ENTRY, Hasher> right_part;
unordered_set<ENTRY, Hasher> used;
map<ENTRY, ENTRY> to_left_part;
 
const ENTRY d[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
 
 
 
bool dfs(ENTRY e)
{
    if (used.find(e) != used.end()) { return false; }
    used.insert(e);
    for (ENTRY diff : d)
    {
        ENTRY next = { e.first + diff.first, e.second + diff.second };
        if (right_part.find(next) == right_part.end()) { continue; }
        if (to_left_part.find(next) == to_left_part.end()
            || dfs(to_left_part[next]))
        {
            to_left_part[next] = e;
            return true;
        }
    }
    return false;
}
 
void kuhn()
{
    for (int i = 0; i < left_part.size(); i++)
    {
        used.clear();
        dfs(left_part[i]);
    }
}
 
int main()
{
    long long int n, m, a, b;
    cin >> n >> m >> a >> b;
    
    long long int free = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c; cin >> c;
            if (c != '.')
            {
                if ((i + j) % 2)
                {
                    right_part.insert({ i, j });
                }
                else
                {
                    left_part.push_back({ i, j });
                }
                free++;
            }
        }
    }
 
    long long int answ = 0;
    if (2 * b < a)
    {
        answ = free * b;
    }
    else
    {
        kuhn();
        answ = to_left_part.size() * a + (free - 2LL * to_left_part.size()) * b;
    }
 
    cout << answ;
    return 0;
}
