#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    freopen("king2.in", "r", stdin);
    freopen("king2.out", "w", stdout);

    vector<vector<int>> matrix(8, vector<int>(8));
    for (auto &row : matrix)
    {
        for (auto &entry : row)
        {
            cin >> entry;
        }
    }

    vector<vector<int>> dp(8, vector<int>(8, 0));

    dp[7][0] = matrix[7][0];

    for (int i = 6; i >= 0; i--) {
        dp[i][0] = dp[i+1][0] + matrix[i][0];
    }

    for (int j = 1; j <= 7; j++) {
        dp[7][j] = dp[7][j-1] + matrix[7][j];
    }

    for (int i = 6; i >= 0; i--) {
        for (int j = 1; j <= 7; j++) {
            dp[i][j] = matrix[i][j] + min({dp[i+1][j-1], dp[i][j-1], dp[i+1][j]});
        }
    }

    cout << dp[0][7];
    return 0;
}