#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
bool is_prime(int n)
{
    if (n < 2) 
        return false;
    for (int i = 2; i * i < n; i++)
    {
        if (!(n % i))
            return false;
    }
    return true;
}
 
vector<int> bebebe(int n)
{
    vector<int> answ;
    int copy_n = n;
    for (int i = 2; i * i <= copy_n; i++)
    {
        if (is_prime(i))
            while (!(n % i))
            {
                answ.push_back(i);
                n /= i;
            }
    }
    if (n != 1)
        answ.push_back(n);
    return answ;
}
 
int main()
{
    int n; cin >> n;
    vector<int> answ = bebebe(n);
    sort(answ.begin(), answ.end());
    for (int& i : answ) 
    {
        cout << i << ' ';
    }
    return 0;
}