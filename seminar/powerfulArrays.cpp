#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 200005; // Max number of elements
const int MAXVAL = 1000005; // Max value of elements

int n, t;
long long a[MAXN];
long long cnt[MAXVAL]; // Frequency count array
long long current_ans = 0;
long long answers[MAXN]; // Store results to print in correct order
int BLOCK_SIZE;

struct Query {
    int l, r, id;

    // Compare function for Mo's ordering
    bool operator<(const Query& other) const {
        int block_l = l / BLOCK_SIZE;
        int block_other = other.l / BLOCK_SIZE;
        
        if (block_l != block_other)
            return block_l < block_other;
        
        // Zigzag optimization: If block is odd, r increases; if block is even, r decreases
        return (block_l % 2 == 0) ? (r < other.r) : (r > other.r);
    }
};

void add(int pos) {
    long long val = a[pos];
    long long delta = (2 * cnt[val] + 1) * val;
    current_ans += delta;
    cnt[val]++;
}

void remove(int pos) {
    long long val = a[pos];
    long long delta = (2 * cnt[val] - 1) * val;
    current_ans -= delta;
    cnt[val]--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> t)) return 0;

    // Calculate block size
    BLOCK_SIZE = sqrt(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<Query> queries(t);
    for (int i = 0; i < t; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // Sort queries according to Mo's order
    sort(queries.begin(), queries.end());

    int curL = 1;
    int curR = 0;
    for (const auto& q : queries) {
        // Increase or decrease R
        while (curR < q.r) add(++curR);
        while (curR > q.r) remove(curR--);
        
        // Increase or decrease L
        while (curL < q.l) remove(curL++);
        while (curL > q.l) add(--curL);

        answers[q.id] = current_ans;
    }

    for (int i = 0; i < t; i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}