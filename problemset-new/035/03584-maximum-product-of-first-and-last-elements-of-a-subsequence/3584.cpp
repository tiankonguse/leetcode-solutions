
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
  ll maximumProduct(vector<int>& nums, int k) {
    int n = nums.size();
    ll ans = ll(nums.front()) * ll(nums.back());
    set<ll> h;
    for (int i = k - 1; i < n; i++) {
      const int l = i - k + 1;
      h.insert(nums[l]);
      ll rightVal = nums[i];  // 右指针
      ans = max(ans, (*h.begin()) * rightVal);
      ans = max(ans, (*h.rbegin()) * rightVal);
      if (h.count(0)) {
        ans = max(ans, 0 * rightVal);
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