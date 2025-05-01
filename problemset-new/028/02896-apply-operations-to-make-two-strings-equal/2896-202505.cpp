
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
  int maxFrequencyScore(vector<int>& nums, long long k) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {  // Changed condition to i <= n
      prefix[i] = prefix[i - 1] + nums[i - 1];
    }
    int l = 1, r = 1;
    int ans = 0;
    ll sum = 0;
    auto updateAdd = [&](auto& v) { sum += v; };
    auto updateDel = [&](auto& v) { sum -= v; };
    auto shouldMove = [&](auto& lv, auto& rv) -> bool {
      int mid = (l + r - 1) / 2;  // [l, mid], [mid, r)
      ll v = nums[mid - 1];
      ll leftDiff = (mid - l + 1) * v - (prefix[mid] - prefix[l - 1]);
      ll rightDiff = (prefix[r - 1] - prefix[mid - 1]) - (r - mid) * v;
      return leftDiff + rightDiff > k;
    };
    while (r <= n) {
      auto& rv = nums[r - 1];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (l < r && shouldMove(nums[l - 1], rv)) {  // 第二步：移动左指针
        auto& lv = nums[l - 1];
        l++;
        updateDel(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
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