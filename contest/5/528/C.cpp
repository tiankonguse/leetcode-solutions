
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
  ll maxDifference(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
      return nums[0];
    } else if (n == 2) {
      return ll(nums[0]) + ll(nums[1]);
    }
    vector<pair<ll, ll>> sg(n + 1, {0, 0});
    sg[n - 1] = {nums[n - 1], 0};
    sg[n - 2] = {ll(nums[n - 1]) + ll(nums[n - 2]), 0};
    for (int i = n - 3; i >= 0; i--) {
      // 选择一个：
      pair<ll, ll> v1 = {sg[i + 1].second + nums[i], sg[i + 1].first};
      if (nums[i] % 3 != 0) {
        v1 = {sg[i + 1].first + nums[i], sg[i + 1].second};
      }
      // 选择两个
      ll sum = nums[i] + nums[i + 1];
      pair<ll, ll> v2 = {sum + sg[i + 2].second, sg[i + 2].first};
      if (sum % 3 != 0) {
        v2 = {sum + sg[i + 2].first, sg[i + 2].second};
      }
      sg[i] = max(v1, v2);
    }
    return sg[0].first - sg[0].second;
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