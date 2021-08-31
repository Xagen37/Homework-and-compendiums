#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
 
using namespace std;
 
void rec(vector<complex<double>>& v, bool invert)
{
    int n = v.size();
    if (n == 1)
        return;
    
    vector<complex<double>> even(n / 2), odd(n / 2);
    for (int i = 0, k = 0; i < n; i += 2, k++)
    {
        even[k] = v[i];
        odd[k] = v[i + 1];
    }
    rec(even, invert);
    rec(odd, invert);
    
    double ang = 2 * 3.1415926535 / n * (invert ? -1 : 1);
    
    complex<double> w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++)
    {
        v[i] = even[i] + w * odd[i];
        v[i + n / 2] = even[i] - w * odd[i];
        w *= wn;
        if (invert)
        {
            v[i] /= 2;
            v[i + n / 2] /= 2;
        }
    }
}
 
vector<long long int> fft(vector<long long int>& a_int, vector<long long int>& b_int)
{
    vector<complex<double>> aa(a_int.begin(), a_int.end());
    vector<complex<double>> bb(b_int.begin(), b_int.end());
 
    long long int size = 1;
    while (size < aa.size() || size < bb.size())
        size <<= 1;
    size <<= 1;
    
    aa.resize(size); bb.resize(size); 
    rec(aa, false); rec(bb, false);
    for (int i = 0; i < size; i++)
        aa[i] *= bb[i];
        
    rec(aa, true);
    
    vector<long long int> to_return(size);
    for (int i = 0; i < size; i++)
        to_return[i] = aa[i].real() + 0.5;
    
    return to_return;
}
 
int main()
{
    long long int n; cin >> n; n++;
    vector <long long int> a(n), b(n);
    for (int i = 0; i < a.size(); i++)
        cin >> a[i];
    for (int i = 0; i < b.size(); i++)
        cin >> b[i];    
    
    vector<long long int> answ = fft(a, b);
    n--;
    for (auto it = answ.end(); it != answ.begin();)
    {
        it--;
        if (*it == 0)
            answ.erase(it);
        else
            break;
    }
    for (int i = 0; i < answ.size(); i++)
        cout << answ[i] << ' ';
    
    return 0;
}