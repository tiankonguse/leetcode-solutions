
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
  int countGoodRotations(vector<int>& nums) {
    int n = nums.size();
    int n2 = n * 2;
    nums.reserve(n2);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      nums.push_back(nums[i]);
      sum += nums[i];
    }
    vector<ll> preSum(n2 + 1, 0);
    for (int i = 0; i < n2; i++) {
      preSum[i + 1] = preSum[i] + nums[i];
    }
    auto Check = [&](int l) -> bool {
      l++;                    // 1-based
      int r = l + n / 2 - 1;  // left half
      ll leftSum = preSum[r] - preSum[l - 1];
      ll rightSum = sum - leftSum;
      return leftSum > rightSum;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (Check(i)) ans++;
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