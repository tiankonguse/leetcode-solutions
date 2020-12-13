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

enum { Alice = 0, Bob = 1 };
enum { Dayu = 0, Xiaoyu = 1 };
ll dp[max3][max3][2][2];  // Alice  希望差值最大， Bob  希望差值最小
ll sum[max3];

class Solution {
  ll myabs(ll a) {
    if (a < 0) {
      return -a;
    } else {
      return a;
    }
  }
  void dfs(int l, int r, int k) {
    if (dp[l][r][k][0] != inf || dp[l][r][k][1] != inf) {
      return;
    }

    if (l == r) {
      dp[l][r][k][0] = 0;
      dp[l][r][k][1] = 0;
      return;
    }

    dfs(l + 1, r, 1 - k);
    dfs(l, r - 1, 1 - k);

    ll DayuTmp = 0;
    ll XiaoyuTmp = 0;
    if (k == Alice) {
      DayuTmp = -inf;   // 大于的时候，希望正数更大，所以取 max
      XiaoyuTmp = inf;  // 小于的时候，希望负数更小，所以取 min
      for (int i = 0; i < 2; i++) {
        ll now = 0;
        ll tmpDayu = 0;
        ll tmpXiaoyu = 0;

        if (i == 0) {  // 选择左边  //[l+1, r]
          now = sum[r] - sum[l];
          tmpDayu = dp[l + 1][r][1 - k][Dayu];
          tmpXiaoyu = dp[l + 1][r][1 - k][Xiaoyu];
        } else {  // 选右边
          now = sum[r - 1] - sum[l - 1];
          tmpDayu = dp[l][r - 1][1 - k][Dayu];
          tmpXiaoyu = dp[l][r - 1][1 - k][Xiaoyu];
        }

        if (tmpXiaoyu != inf) {  // Bob <=  Alice
          DayuTmp = max(DayuTmp, now + tmpXiaoyu);
        }

        if (tmpDayu != inf) {  // Bob >= Alice
          if (now >= tmpDayu) {
            DayuTmp = max(DayuTmp, now - tmpDayu);
          }
          if (now <= tmpDayu) {
            XiaoyuTmp = min(XiaoyuTmp, now - tmpDayu);
          }
        }
      }
    } else if (k == Bob) {
      DayuTmp = inf;     // 大于的时候，希望正数更小
      XiaoyuTmp = -inf;  // 小于的时候，希望负数更大
      for (int i = 0; i < 2; i++) {
        ll now = 0;
        ll tmpDayu = 0;
        ll tmpXiaoyu = 0;
        if (i == 0) {  // 选左边
          now = sum[r] - sum[l];
          tmpDayu = dp[l + 1][r][1 - k][Dayu];
          tmpXiaoyu = dp[l + 1][r][1 - k][Xiaoyu];
        } else {  //选右边
          now = sum[r - 1] - sum[l - 1];
          tmpDayu = dp[l][r - 1][1 - k][Dayu];
          tmpXiaoyu = dp[l][r - 1][1 - k][Xiaoyu];
        }

        if (tmpXiaoyu != inf) {  //  Alice <= Bob
          DayuTmp = min(DayuTmp, now + tmpXiaoyu);
        }

        if (tmpDayu != inf) {  //  Alice >= Bob
          if (now >= tmpDayu) {
            DayuTmp = min(DayuTmp, now - tmpDayu);
          }
          if (now <= tmpDayu) {
            XiaoyuTmp = max(XiaoyuTmp, now - tmpDayu);
          }
        }
      }
    }

    dp[l][r][k][Dayu] = myabs(DayuTmp);
    dp[l][r][k][Xiaoyu] = myabs(XiaoyuTmp);
    printf("l=%d r=%d k=%d dayu[%lld] xiaoyu[%lld]\n", l, r, k,
           dp[l][r][k][Dayu], dp[l][r][k][Xiaoyu]);
    return;
  }

 public:
  int stoneGameVII(vector<int>& str) {
    int n = str.size();
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        for (int k = 0; k < 2; k++) {
          dp[i][j][k][0] = dp[i][j][k][1] = inf;
        }
      }
    }
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + str[i - 1];
    }

    dfs(1, n, Alice);
    // ll ans = -inf;
    // if (dp[1][n][Alice][Dayu] != inf) {
    //   ans = max(ans, dp[1][n][Alice][Dayu]);
    // }
    // if (dp[1][n][Alice][Xiaoyu] != inf) {
    //   ans = max(ans, dp[1][n][Alice][Xiaoyu]);
    // }

    return dp[1][n][Alice][Dayu];
  }
};

int main() {
  TEST_SMP1(Solution, stoneGameVII, 6, vector<int>({5, 3, 1, 4, 2}));
  // TEST_SMP1(Solution, stoneGameVII, 122,
  //           vector<int>({7, 90, 5, 1, 100, 10, 10, 2}));

  return 0;
}
