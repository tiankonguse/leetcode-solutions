/*
[1,3,3]
[7,8,19] 1*19
[10,20,18] 11个
[21,22,6]
[34,37,5]
[47,50,3]

k=13
ans=218
*/
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
  ll maximumCoins(vector<vector<int>>& nums, ll k) {
    // nums[i] = [li, ri, ci]
    int n = nums.size();
    sort(nums.begin(), nums.end());

    auto SolverRight = [&]() {
      int l = 0, r = 0;
      ll ans = 0;
      ll sum = 0;
      auto updateAdd = [&](auto& v) {
        ll li = v[0], ri = v[1], ci = v[2];
        sum += (ri - li + 1) * ci;
      };
      auto updateDel = [&](auto& v) {
        ll li = v[0], ri = v[1], ci = v[2];
        sum -= (ri - li + 1) * ci;
      };
      auto shouldMove = [&](auto& lv, auto& rv) -> bool { return rv[1] - lv[1] >= k; };
      while (r < n) {
        auto& rv = nums[r];
        r++;
        updateAdd(rv);  // 第一步：移动右指针

        while (l < r && shouldMove(nums[l], rv)) {  // 第二步：移动左指针
          auto& lv = nums[l];
          l++;
          updateDel(lv);
        }
        auto& lv = nums[l];
        if (rv[1] - lv[0] + 1 > k) {  // 超过 k 个，需要截断
          // 策略2: 左侧 [lv[0], rv[1]-k] 不选择， 优先选择右半侧 [rv[1]-k+1, rv[1]]
          ll excess = rv[1] - lv[0] + 1 - k;
          ll sum2 = sum - excess * lv[2];
          ans = max(ans, sum2);  // 第三步：更新答案
        } else {
          ans = max(ans, sum);  // 第三步：更新答案
        }
      }
      return ans;
    };

    ll ans1 = SolverRight();
    for (auto& v : nums) {
      swap(v[0], v[1]);
      v[0] = -1 * v[0];
      v[1] = -1 * v[1];
    }
    sort(nums.begin(), nums.end());
    ll ans2 = SolverRight();

    return max(ans1, ans2);
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