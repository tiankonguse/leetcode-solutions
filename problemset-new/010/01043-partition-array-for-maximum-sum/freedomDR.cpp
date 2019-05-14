#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int len = A.size();
        vector<int> dp(len+1, 0);
        for(int i = 0; i < len; ++i) {
            int maxx = 0;
            for(int k = 1; k <= K && i-k+1 >= 0; k++) {
                maxx = max(A[i-k+1], maxx);
                dp[i+1] = max(dp[i+1], dp[i+1-k]+maxx*k);
            }
        }
        return dp[len];
    }
};

int main()
{
    return 0;
}
