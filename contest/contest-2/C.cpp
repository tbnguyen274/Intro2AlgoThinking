#include <iostream>
using namespace std;

/*
Check:
- All odd numbers in the array are in non-decreasing order
- All even numbers in the array are in non-decreasing order
*/

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        int oddIndex = -1;
        int evenIndex = -1;
        bool valid = true;
        
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            
            if (x % 2 == 1) {
                if (oddIndex != -1 && x < oddIndex) {
                    valid = false;
                }
                oddIndex = x;
            } else {
                if (evenIndex != -1 && x < evenIndex) {
                    valid = false;
                }
                evenIndex = x;
            }
        }
        
        cout << (valid ? "Yes" : "No") << "\n";
    }
    
    return 0;
}
