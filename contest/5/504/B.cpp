
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
  int maximumSaleItems(vector<vector<int>>& items, int budget) {  //
    int n = items.size();
    vector<int> gain(n, 0);
    for (int i = 0; i < n; i++) {
      int cnt = 1;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (items[j][0] % items[i][0] == 0) cnt++;
      }
      gain[i] = cnt;
    }

    vector<int> dp(budget + 1, 0);
    int ans = 0;
    int minCost = INT_MAX;
    for (int i = 0; i < n; i++) {
      int cost = items[i][1];
      minCost = min(minCost, cost);
      for (int b = budget; b >= cost; --b) {
        dp[b] = max(dp[b], dp[b - cost] + gain[i]);
      }
    }
    for (int b = 0; b <= budget; b++) {
      ans = max(ans, dp[b] + (budget - b) / minCost);
    }
    return ans;
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