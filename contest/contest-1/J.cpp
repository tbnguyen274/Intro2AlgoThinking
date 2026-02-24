#include <iostream>
using namespace std;

int main() {
    freopen("badsubs.in", "r", stdin);
    freopen("badsubs.out", "w", stdout);
    
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }
    
    long long dp[23][3];
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[1][0] = 1;
    dp[1][1] = 1;
    dp[1][2] = 1;
    
    for (int i = 1; i < n; i++) {
        dp[i+1][0] = dp[i][0] + dp[i][1] + dp[i][2];
        dp[i+1][1] = dp[i][1] + dp[i][2];
        dp[i+1][2] = dp[i][0] + dp[i][1] + dp[i][2];
    }
    
    long long result = dp[n][0] + dp[n][1] + dp[n][2];
    cout << result << endl;
    
    return 0;
}