#include <iostream>
#include <set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    set<int> attackedRows;
    set<int> attackedCols;
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        
        attackedRows.insert(x);
        attackedCols.insert(y);
        
        long long r = attackedRows.size();
        long long c = attackedCols.size();
        long long notUnderAttack = (n - r) * (n - c);
        
        cout << notUnderAttack << "\n";
    }
    
    return 0;
}
