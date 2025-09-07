
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
const int B = 20;
const int MaxVal = 1 << B;
int dp[MaxVal];
class Solution {
 public:
  long long maxProduct(vector<int>& nums) {
    int n = nums.size();
    int maxVal = *max_element(nums.begin(), nums.end());
    int maxBit = 0;
    while ((1 << maxBit) <= maxVal) {
      maxBit++;
    }
    const int MaxBitVal = 1 << maxBit;
    fill_n(dp, MaxBitVal, 0);
    for (auto v : nums) {
      dp[v] = v;
    }
    for (int i = 0; i < MaxBitVal; i++) {
      for (int j = 0; j < maxBit; j++) {
        dp[i | (1 << j)] = max(dp[i | (1 << j)], dp[i]);
      }
    }
    ll ans = 0;
    for (ll v : nums) {
      int complement = (MaxBitVal - 1) ^ v;
      ans = max(ans, v * dp[complement]);
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