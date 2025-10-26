
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
  ll numGoodSubarrays(vector<int>& nums1, int k) {
    int n = nums1.size();
    vector<pair<ll, ll>> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
      int v = nums1[i];
      if (nums.empty() || nums.back().first != v) {
        nums.push_back({v, 1});
      } else {
        nums.back().second++;
      }
    }

    ll sum = 0;
    ll ans = 0;
    unordered_map<ll, ll> count;
    count[0] = 1;
    for (auto& [v, cnt] : nums) {
      ll sum0 = sum;  // 不包含 v 的前缀和
      for (ll i = 1; i <= cnt; i++) {
        sum0 += v;
        if (count.count(sum0 % k)) {
          ans += count[sum0 % k];
        }
      }
      // 第二步：延迟更新计数器
      for (ll i = 1; i <= cnt; i++) {
        sum += v;
        count[sum % k]++;
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