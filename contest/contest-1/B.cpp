#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    freopen("lepus.in", "r", stdin);
    freopen("lepus.out", "w", stdout);

    int n;
    string s;
    cin >> n >> s;

    char swamp = 'w', grass = '"';
    vector<int> dp(n, -1);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] != swamp) {
            int isGrass = (s[i] == grass);
            
            if (dp[i - 1] != -1) {
                dp[i] = max(dp[i], dp[i - 1] + isGrass);
            }

            if (i >= 3 && dp[i - 3] != -1) {
                dp[i] = max(dp[i], dp[i - 3] + isGrass);
            }

            if (i >= 5 && dp[i - 5] != -1) {
                dp[i] = max(dp[i], dp[i - 5] + isGrass);
            }
        }
    }

    cout << dp[n - 1];

    return 0;
}