#include <iostream>
#include <vector>

using namespace std;

int main()
{

    freopen("peacefulsets.in", "r", stdin);
    freopen("peacefulsets.out", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int>> dp(12, vector<int>(n + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        int power = 1;
        for (int j = 0; j < 12 && power <= i; ++j)
        {
            for (int k = 0; k <= j; ++k)
            {
                dp[j][i] += dp[k][i - power];
            }
            power = (power << 1) | 1;
        }
    }

    long long result = 0;
    for (int j = 0; j < 12; ++j)
    {
        result += dp[j][n];
    }

    cout << result;
    return 0;
}