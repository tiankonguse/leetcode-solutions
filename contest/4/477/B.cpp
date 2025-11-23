
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
  int maxBalancedSubarray(vector<int>& nums) {
    map<pair<ll, ll>, ll> H;  // <xor, oddEven> -> index
    ll preXor = 0, PreOddEven = 0;
    H[{preXor, PreOddEven}] = 0;
    int n = nums.size();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ll v = nums[i - 1];
      preXor ^= v;
      if (v % 2 == 0) {
        PreOddEven++;
      } else {
        PreOddEven--;
      }
      pair<ll, ll> key = {preXor, PreOddEven};
      if (H.count(key)) {  // 最长，不覆盖
        ans = max(ans, i - H[key]);
      } else {
        H[key] = i;
      }
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