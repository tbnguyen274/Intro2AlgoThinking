#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double PI = 3.1415926536;

int main() {
    int n;
    cin >> n;
    
    vector<int> radii(n);
    for (int i = 0; i < n; i++) {
        cin >> radii[i];
    }
    
    // Sort in descending order
    sort(radii.begin(), radii.end(), greater<int>());
    
    double totalArea = 0.0;
    
    for (int i = 0; i < n; i++) {
        double area = PI * radii[i] * radii[i];
        if (i % 2 == 0) {
            totalArea += area;
        } else {
            totalArea -= area;
        }
    }
    
    cout << totalArea << "\n";
    
    return 0;
}
