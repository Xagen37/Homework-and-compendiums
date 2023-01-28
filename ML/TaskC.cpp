#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using obj_t = pair<vector<int>, int>;

constexpr double PI = 3.14159265358979323846;

double manhattan(const vector<int>& x1, const vector<int>& x2)
{
    double sum = 0;
    const int size = x1.size();
    for (int i = 0; i < size; i++)
    {
        sum += abs(x1[i] - x2[i]);
    }
    return sum;
}

double euclid(const vector<int>& x1, const vector<int>& x2)
{
    double sum = 0;
    const int size = x1.size();
    for (int i = 0; i < size; i++)
    {
        const double diff = x1[i] - x2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

double chebyshev(const vector<int>& x1, const vector<int>& x2)
{
    double sum = -1;
    const int size = x1.size();
    for (int i = 0; i < size; i++)
    {
        sum = max(static_cast<double>(abs(x1[i] - x2[i])), sum);
    }
    return sum;
}

double uniform(const double& arg)
{
    if (abs(arg) < 1)
        return 0.5;
    return 0;
}

double triangular(const double& arg)
{
    if (abs(arg) <= 1)
        return 1 - abs(arg);
    return 0;
}

double epanechnikov(const double& arg)
{
    if (abs(arg) <= 1)
        return (1 - arg * arg) * 0.75;
    return 0;
}

double quartic(const double& arg)
{
    if (abs(arg) <= 1)
    {
        double diff = 1 - arg * arg;
        return (15.0 / 16.0) * diff * diff;
    }
    return 0;
}

double triweight(const double& arg)
{
    if (abs(arg) <= 1)
    {
        double diff = 1 - arg * arg;
        return (35.0 / 32.0) * diff * diff * diff;
    }
    return 0;
}

double tricube(const double& arg)
{
    if (abs(arg) <= 1)
    {
        double absed = abs(arg);
        double diff = 1 - absed * absed * absed;
        return (70.0 / 81.0) * diff * diff * diff;
    }
    return 0;
}

double gaussian(const double& arg)
{
    return 1.0 / (sqrt(2.0 * PI)) * exp(-0.5 * arg * arg);
}

double cosine(const double& arg)
{
    if (abs(arg) <= 1)
    {
        return PI / 4.0 * cos(PI / 2.0 * arg);
    }
    return 0;
}

double logistic(const double& arg)
{
    return 1.0 / (2 + exp(arg) + exp(-arg));
}

double sigmoid(const double& arg)
{
    return 2.0 / (PI * (exp(arg) + exp(-arg)));
}

struct algo
{
    double (*dist_f)(const vector<int>& x1, const vector<int>& x2) = nullptr;
    double (*kernel_f)(const double& arg) = nullptr;

    algo(const string& dist, const string& kernel)
    {
        switch (dist[0])
        {
            case 'c': dist_f = chebyshev; break;
            case 'e': dist_f = euclid; break;
            case 'm': dist_f = manhattan; break;
        }

        switch (kernel[0])
        {
            case 'c': kernel_f = cosine; break;
            case 'e': kernel_f = epanechnikov; break;
            case 'g': kernel_f = gaussian; break;
            case 'l': kernel_f = logistic; break;
            case 'q': kernel_f = quartic; break;
            case 's': kernel_f = sigmoid; break;
            case 'u': kernel_f = uniform; break;
            default:
                switch (kernel[3])
                {
                    case 'a': kernel_f = triangular; break;
                    case 'c': kernel_f = tricube; break;
                    case 'w': kernel_f = triweight; break;
                }
        }
    }
};

struct knn
{
    algo a;
    char window_name;
    int win_param;
    vector<obj_t> objects;

    knn(const string& dist, const string& kernel, const string& window, int param, vector<obj_t>&& objs)
        : a(dist, kernel)
        , window_name(window[0])
        , win_param(param)
        , objects(move(objs))
    {}

    double find_nearest(const vector<int>& features)
    {
        vector<pair<double, int>> dists(objects.size());
        for (int i = 0; i < objects.size(); i++)
        {
            dists[i] = { a.dist_f(features, objects[i].first), objects[i].second };
        }
        sort(dists.begin(), dists.end(), [](const pair<double, int>& lhs, const pair<double, int>& rhs) { return lhs.first < rhs.first; });

        double weighted = 0.0, all = 0.0;
        double border = window_name == 'f' ? win_param : dists[win_param].first;
        if (border < 1e-7)
        {
            double aver = 0.0; int cnt = 0;
            for (int i = 0; i < objects.size(); i++)
            {
                if (objects[i].first == features)
                {
                    aver += objects[i].second;
                    cnt++;
                }
            }
            return aver / cnt;
        }

        for (int i = 0; i < objects.size(); i++)
        {
            double windowed = window_name == 'f' ? dists[i].first / border : dists[i].first / border;
            double kerneled = a.kernel_f(windowed);
            weighted += dists[i].second * kerneled;
            all += kerneled;
        }
        if (abs(all) < 1e-7)
        {
            double aver = 0.0;
            for (int i = 0; i < objects.size(); i++)
            {
                aver += objects[i].second;
            }
            return aver / objects.size();
        }
        else
        {
            return weighted / all;
        }
    }
};

int main()
{
    int n, m; cin >> n >> m;

    vector<obj_t> objs(n);
    for (int i = 0; i < n; i++)
    {
        objs[i].first.resize(n);
        for (int j = 0; j < m; j++)
        {
            cin >> objs[i].first[j];
        }
        cin >> objs[i].second;
    }

    vector<int> query(m);
    for (int i = 0; i < m; i++)
    {
        cin >> query[i];
    }

    string dist; cin >> dist;
    string kernel; cin >> kernel;
    string window; cin >> window;
    int win_param; cin >> win_param;

    knn algo(dist, kernel, window, win_param, move(objs));

    cout << setprecision(20) << algo.find_nearest(query);

    return 0;
}