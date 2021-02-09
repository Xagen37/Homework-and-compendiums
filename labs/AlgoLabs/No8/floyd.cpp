#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  const int INF = 1000000;
  int n;
  cin >> n;
  vector <vector <int>> dp(n, vector <int>(n, INF));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> dp[i][j];
    }
  }

  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
      for (int k = 0; k < n; k++)
      {
        if (dp[j][i] != INF && dp[i][k] != INF)
        {
          dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]);
        }
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}