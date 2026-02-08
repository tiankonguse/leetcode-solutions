
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
ll dp[111][111][111];
class Solution {
public:
    ll maxScore(vector<int>& nums1, vector<int>& nums2, int K) {
        int n = nums1.size();
        int m = nums2.size();
        for(int i=0;i<=n;i++){
          for(int j=0;j<=m;j++){
            //k = 0
            dp[i][j][0] = 0;
            const int nm = min(min(i, j), K);
            for(int k=1;k<=nm;k++){
              dp[i][j][k] = INT64_MIN;
              if(i > k && j  >= k){
                dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
              }
              if(i >= k && j > k){
                dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k]);
              }
              if(i > k && j > k){
                dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k]);
              }
              if(i >= k && j >= k){
                dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1] + ll(nums1[i-1]) * ll(nums2[j-1]));
              }
            }
          }
        }
        return dp[n][m][K];
    }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif