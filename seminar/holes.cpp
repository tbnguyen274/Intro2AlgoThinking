#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, q, blockSize;
vector<int> jump;           // jump power at each position
vector<int> nextOut;        // next position that jumps out of the block from i
vector<int> jumpCount;      // number of small steps to reach nextOut[i]

// Rebuild the block containing startIndex
void rebuildBlock(int startIndex) {
    // 1-indexed
    int id = (startIndex - 1) / blockSize;
    int leftBound = id * blockSize + 1;

    for (int i = startIndex; i >= leftBound; --i) {
        int target = i + jump[i];

        // If jumps out of the array or to a different block
        if (target > n || (target - 1) / blockSize != (i - 1) / blockSize) {
            nextOut[i] = target;
            jumpCount[i] = 1;
        }
        // If still in the same block
        else {
            nextOut[i] = nextOut[target];
            jumpCount[i] = jumpCount[target] + 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    // Calculate block size
    blockSize = max(1, (int)sqrt(n));

    jump.assign(n + 2, 0);
    nextOut.assign(n + 2, 0);
    jumpCount.assign(n + 2, 0);

    for (int i = 1; i <= n; ++i) cin >> jump[i];

    // PREPROCESSING: build nextOut and jumpCount
    for (int i = n; i >= 1; --i) {
        int target = i + jump[i];

        if (target > n || (target - 1) / blockSize != (i - 1) / blockSize) {
            nextOut[i] = target;
            jumpCount[i] = 1;
        } else {
            nextOut[i] = nextOut[target];
            jumpCount[i] = jumpCount[target] + 1;
        }
    }

    // PROCESS QUERIES
    while (q--) {
        int type;
        cin >> type;

        // UPDATE: jump[pos] = val
        if (type == 0) {
            int pos, val;
            cin >> pos >> val;
            jump[pos] = val;

            rebuildBlock(pos);  // Rebuild the block containing pos
        }

        else {
            // QUERY: output final position + number of steps
            int curPos;
            cin >> curPos;

            int totalSteps = 0;

            // Jump by blocks first
            while (curPos <= n && nextOut[curPos] <= n) {
                totalSteps += jumpCount[curPos];
                curPos = nextOut[curPos];
            }

            // Jump by individual steps when outside the block
            while (curPos + jump[curPos] <= n) {
                curPos += jump[curPos];
                totalSteps++;
            }

            totalSteps++; // final step jumps out of the array

            cout << curPos << " " << totalSteps << "\n";
        }
    }

    return 0;
}