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

int dp[1 << 16][17];

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

  int solver() {
    // printf("solver\n");
    num = n / k;  //一组的个数
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) {
      //   printf("i=%d v=%d mask=%d\n", i, nums[i], 1 << i);
    }

    memset(dp[0], 0, sizeof(dp[0]));
    for (int mask = 0; mask < (1 << n); mask++) {
      //遍历到 mask ，说明mask 的所有 pre 都已经计算了，可以更新为最优值了

      if (__builtin_popcount(mask) % num == 0) {
        // printf("mask num = %d\n", __builtin_popcount(mask));
        int minAns = dp[mask][0];
        for (int pre = 0; pre < n; pre++) {
          minAns = min(minAns, dp[mask][pre]);
        }
        for (int i = 0; i < n; i++) {
          if (mask & (1 << i)) continue;  //
          int tmp = mask | (1 << i);
          dp[tmp][i] = min(dp[tmp][i], minAns);

          //   printf("mask=%d v=%d i=%d newmask=%d newv=%d\n", mask, minAns, i,
          //   tmp,
          //          dp[tmp][i]);
        }
      } else {
        for (int pre = 0; pre < n; pre++) {
          if ((mask & (1 << pre)) == 0) continue;  // pre 不在 mask 中

          for (int i = pre + 1; i < n; i++) {
            //递推出可以到达的下一个合法位置
            if (nums[i] == nums[pre]) continue;  //选择的数字不能和 pre相同
            if (mask & (1 << i)) continue;       //
            int tmp = mask | (1 << i);
            dp[tmp][i] = min(dp[tmp][i], dp[mask][pre] + nums[i] - nums[pre]);
            // printf("mask=%d pre=%d v=%d i=%d newmask=%d newv=%d\n", mask,
            // pre,
            //        dp[mask][pre], i, tmp, dp[tmp][i]);
          }
        }
      }
    }
    // for (int i = 0; i < 1 << n; i++) {
    //   for (int pre = 0; pre < n; pre++) {
    //     printf("mask=%d pre=%d v=%d\n", i, pre, dp[i][pre]);
    //   }
    // }
    return dp[(1 << n) - 1][n - 1];  //答案就是全选
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
