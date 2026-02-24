#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;
    
    int m;
    cin >> m;
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        
        // Conditions:
        // 1. x + y >= d
        // 2. x + y <= 2n - d
        // 3. |x - y| <= d
        
        bool isInside = (x + y >= d) && 
                      (x + y <= 2 * n - d) && 
                      (abs(x - y) <= d);
        
        if (isInside) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
