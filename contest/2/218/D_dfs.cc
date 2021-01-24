#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  int n;
  int k;
  int num;
  vector<int> nums;
  int check() {
    map<int, int> m;
    int maxNum = 0;
    for (auto v : nums) {
      m[v]++;
      maxNum = max(maxNum, m[v]);
    }
    // printf("maxNum=%d\n", maxNum);
    return maxNum;
  }

  int ok(int state) {
    int bit = 0;
    int minVal = 17, maxVal = -1;
    while (state) {
      int i = __builtin_popcount(state ^ (state - 1)) - 1;
      if (bit & (1 << nums[i])) return -1;
      minVal = min(minVal, nums[i]);
      maxVal = max(maxVal, nums[i]);
      bit |= 1 << nums[i];
      state &= state - 1;
    }
    return maxVal - minVal;
  }

  vector<int> dp;
  int dfsUp(const int state) {  // 从小到大枚举
    if (state + 1 == 1 << n) {
      return 0;
    }
    if (dp[state] != -2) {
      return dp[state];
    }

    int ans = -1;
    for (int i = 0; i < 1 << n; i++) {
      if (i & state) continue;                     // 重复
      if (__builtin_popcount(i) != num) continue;  //必须选 Num 个
      int retLeft = ok(i);                         //
      if (retLeft < 0) {
        // printf("i=%d not ok\n", i);
        continue;
      }
      int retRight = dfsUp(state | i);
      if (retRight < 0) {
        // printf("i=%d not ok\n", state | i);
        continue;
      }
      if (ans < 0) {
        ans = retLeft + retRight;
      } else {
        ans = min(ans, retLeft + retRight);
      }
    }
    return dp[state] = ans;
  }

  int dfsDown(const int state) {
    if (state == 0) {
      return 0;
    }
    if (dp[state] != -2) {
      return dp[state];
    }

    int ans = 100000;
    for (int i = state; i; i = (i - 1) & state) {
      if (__builtin_popcount(i) != num) continue;
      int retLeft = ok(i);  //
      if (retLeft < 0) {
        // printf("i=%d not ok\n", i);
        continue;
      }
      if (retLeft >= ans) {
        continue;
      }

      int retRight = dfsDown(state ^ i);
      if (retRight < 0) {
        // printf("i=%d not ok\n", state ^ i);
        continue;
      }

      if (ans < 0) {
        ans = retLeft + retRight;
      } else {
        ans = min(ans, retLeft + retRight);
      }
    }

    return dp[state] = ans;
  }

  int solver() {
    // printf("solver\n");
    num = n / k;  //一组的个数
    dp.clear();
    dp.resize(1 << n, -2);
    return dfsDown((1 << n) - 1);  //答案就是全选
  }

 public:
  int minimumIncompatibility(vector<int>& nums_, int k_) {
    nums.swap(nums_);
    k = k_;
    n = nums.size();
    sort(nums.begin(), nums.end());
    if (check() > k) {  //只要个数不大于 k，扫描线的方式肯定可以找到一个答案
      return -1;
    }
    int n = nums.size();
    if (k == n) {
      return 0;  //一个数字，差值是 0
    }
    if (k == 1) {  //一个分组，最大值减去最小值
      return nums[n - 1] - nums[0];
    }
    return solver();
  }
};

int main() {
  TEST_SMP2(Solution, minimumIncompatibility, 4, vector<int>({1, 2, 1, 4}), 2);
  TEST_SMP2(Solution, minimumIncompatibility, 6,
            vector<int>({6, 3, 8, 1, 3, 1, 2, 2}), 4);
  TEST_SMP2(Solution, minimumIncompatibility, -1,
            vector<int>({5, 3, 3, 6, 3, 3}), 3);
  TEST_SMP2(Solution, minimumIncompatibility, -1, vector<int>({1, 1}), 1);
  return 0;
}
