
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
class Solution {
 public:
  int maxBalancedShipments(vector<int>& weight) {
    int n = weight.size();
    vector<int> preMax(n, -1);
    vector<int> sta;
    sta.reserve(n);
    for (int i = 0; i < n; i++) {
      while (!sta.empty() && weight[sta.back()] <= weight[i]) {
        sta.pop_back();
      }
      preMax[i] = sta.empty() ? -1 : sta.back();
      sta.push_back(i);
    }
    int ans = 0;
    vector<int> dp(n, 0);
    for (int i = 1; i < n; i++) {
      dp[i] = dp[i - 1];
      if (preMax[i] != -1) {
        if (preMax[i] > 0) {
          dp[i] = max(dp[i], dp[preMax[i] - 1] + 1);
        } else {
          dp[i] = max(dp[i], 1);
        }
      }
    }

    return dp[n - 1];
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