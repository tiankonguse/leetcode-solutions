
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
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}

class Solution {
 public:
  int maxLength(vector<int>& nums) {
    int n = nums.size();
    int l = 0, r = 0;
    int ans = 0;
    auto updateAdd = [&](auto& v) {};
    auto updateDel = [&](auto& v) {};
    auto shouldMove = [&](auto& lv, auto& rv) -> bool {
      if (l + 2 >= r) {
        return false;
      }
      auto rrv = nums[r - 2];
      if (Gcd(rv, rrv) != 1) {
        return true;
      }
      for (int i = l; i + 2 < r; i++) {
        if (Gcd(nums[i], rv) != 1 || Gcd(nums[i], rrv) != 1) {
          return true;
        }
      }
      return false;
    };
    while (r < n) {
      auto& rv = nums[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (l < r && shouldMove(nums[l], rv)) {  // 第二步：移动左指针
        auto& lv = nums[l];
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