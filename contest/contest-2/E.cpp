#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<pair<long long, int>> players(n); // (tokens, originalIndex)
        for (int i = 0; i < n; i++) {
            cin >> players[i].first;
            players[i].second = i + 1; // 1-indexed
        }
        
        // Sort by tokens
        sort(players.begin(), players.end());
        
        // Calculate prefix sums
        vector<long long> prefixSum(n);
        prefixSum[0] = players[0].first;
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i-1] + players[i].first;
        }
        
        int minIndex = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (prefixSum[i] >= players[i + 1].first) {
                minIndex = i;
            } else {
                break;
            }
        }
        
        vector<int> winners;
        for (int i = minIndex; i < n; i++) {
            winners.push_back(players[i].second);
        }
        
        // Sort by original index
        sort(winners.begin(), winners.end());
        
        // Output
        cout << winners.size() << "\n";
        for (int i = 0; i < winners.size(); i++) {
            if (i > 0) cout << " ";
            cout << winners[i];
        }
        cout << "\n";
    }
    
    return 0;
}
