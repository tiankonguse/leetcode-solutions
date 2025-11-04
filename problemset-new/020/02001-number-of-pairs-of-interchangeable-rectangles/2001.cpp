
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
  ll interchangeableRectangles(vector<vector<int>>& nums) {
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) { return ll(a[0]) * b[1] < ll(a[1]) * b[0]; });
    ll ans = 0;
    vector<ll> pre;
    ll num = 0;
    for (auto& v : nums) {
      if (num > 0 && pre[0] * v[1] == pre[1] * v[0]) {
        num++;
      } else {
        ans += num * (num - 1) / 2;
        num = 1;
        pre = {v[0], v[1]};
      }
    }
    ans += num * (num - 1) / 2;
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