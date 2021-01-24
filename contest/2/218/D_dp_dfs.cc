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

  int mymin(int a, int b) {
    if (a < 0) return b;
    if (b < 0) return a;
    return min(a, b);
  }

  int dfs(const int mask, const int now) {
    if (dp[mask][now] != -1) {
      return dp[mask][now];
    }

    if (mask & (mask - 1) == 0) {
      return dp[mask][now] = 0;  //只有一个，代价是 0
    }

    int preMask = mask ^ (1 << now);
    int ans = -2;

    // preMask 是整数倍，pre 可以任意值
    if (__builtin_popcount(preMask) % num == 0) {
      for (int i = 0; i < n; i++) {
        if ((preMask & (1 << i)) == 0) continue;  //非法值
        int tmp = dfs(preMask, i);
        if (tmp >= 0) {
          ans = mymin(ans, tmp);
        }
      }
    } else {
      for (int i = 0; i < now; i++) {
        if ((preMask & (1 << i)) == 0) continue;  //非法值
        if (nums[i] == nums[now]) continue;
        int tmp = dfs(preMask, i);
        if (tmp >= 0) {
          ans = mymin(ans, tmp + nums[now] - nums[i]);
        }
      }
    }
    return dp[mask][now] = ans;
  }

  int solver() {
    // printf("solver\n");
    num = n / k;  //一组的个数
    memset(dp, -1, sizeof(dp));
    return dfs((1 << n) - 1, n - 1);  //答案就是全选
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
