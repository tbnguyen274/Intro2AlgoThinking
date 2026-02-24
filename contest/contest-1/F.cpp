#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> generatesizes(int maxBalls)
{
    vector<int> sizes;

    int height = 1;
    int size = 1;
    int total = 1;

    while (total <= maxBalls)
    {
        sizes.push_back(total);

        height++;
        size += height;
        total += size;
    }

    return sizes;
}

vector<int> computeMinPyramids(int maxBalls)
{
    vector<int> dp(maxBalls + 1, INT_MAX);
    dp[0] = 0;

    vector<int> sizes = generatesizes(maxBalls);

    for (int balls = 1; balls <= maxBalls; balls++)
    {
        for (int size : sizes)
        {
            if (size > balls)
                break;

            if (dp[balls - size] != INT_MAX)
            {
                dp[balls] = min(dp[balls], dp[balls - size] + 1);
            }
        }
    }

    return dp;
}

vector<int> read()
{
    int count;
    cin >> count;

    vector<int> testCases(count);
    for (int &tc : testCases)
    {
        cin >> tc;
    }

    return testCases;
}

int main()
{
    vector<int> testCases = read();
    int maxBalls = *max_element(testCases.begin(), testCases.end());

    vector<int> minPyramids = computeMinPyramids(maxBalls);

    for (int balls : testCases)
    {
        cout << minPyramids[balls] << "\n";
    }

    return 0;
}