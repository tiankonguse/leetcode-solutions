/*
在一条数轴上有无限多个袋子，每个坐标对应一个袋子。其中一些袋子里装有硬币。

给你一个二维数组 coins，其中 coins[i] = [li, ri, ci] 表示从坐标 li 到 ri 的每个袋子中都有 ci 枚硬币。

数组 coins 中的区间互不重叠。

另给你一个整数 k。

返回通过收集连续 k 个袋子可以获得的 最多 硬币数量。


[1,3,3]
[7,8,19] 1*19
[10,20,18] 11个
[21,22,6]
[34,37,5]
[47,50,3]
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
    sort(nums.begin(), nums.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

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
    auto shouldMove = [&](auto& lv, auto& rv) -> bool { return rv[1] - lv[0] + 1 >= k; };
    while (r < n) {
      auto& rv = nums[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (l < r && shouldMove(nums[l], rv)) {  // 第二步：移动左指针
        // 此时，保证 rv[1] - lv[0] + 1 >= k;
        auto& lv = nums[l];
        if (rv[0] - lv[0] < k) {
          ll excess = rv[1] - k - lv[0] + 1;
          ll sum1 = sum - excess * rv[2];
          ans = max(ans, sum1);  // 第三步：更新答案
        }
        if (rv[1] - lv[1] < k) {
          ll excess = rv[1] - k - lv[0] + 1;
          ll sum2 = sum - excess * lv[2];
          ans = max(ans, sum2);  // 第三步：更新答案
        }

        l++;
        updateDel(lv);
      }
      ans = max(ans, sum);  // 第三步：更新答案
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