
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
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

class Solution {
  vector<vector<double>> dp1, dp2;
  int MASK;
  vector<int> time;
  vector<pair<int, int>> maskVal;
  vector<double> mul;
  int n, m, k;
  // __builtin_popcount 一的个数

  int nextLoop(const int mi, double useTime) {
    // 时间向下取整
    return (mi + int(floor(useTime))) % m;
  }

 public:
  double minTime(int n_, int k_, int m_, vector<int>& time_, vector<double>& mul_) {
    n = n_;
    m = m_;
    k = k_;
    mul.swap(mul_);
    time.swap(time_);
    if (k == 1) {
      if (n > 1) {
        return -1;
      } else {
        return time[0] * mul[0];
      }
    }
    MASK = 1 << n;
    maskVal.resize(MASK);
    maskVal[0] = {0, 0};
    for (int i = 0; i < n; i++) {
      const int mask = 1 << i;
      for (int j = 0; j < mask; j++) {
        auto [maxTime, oneNum] = maskVal[j];
        maskVal[mask | j] = {max(maxTime, time[i]), oneNum + 1};
      }
    }
    dp1.resize(MASK, vector<double>(m, 1e18));
    dp2.resize(MASK, vector<double>(m, 1e18));
    min_queue<tuple<double, int, int, int>> que;
    que.push({0, 1, MASK - 1, 0});
    dp1[MASK - 1][0] = 0;
    double ans = 1e18;
    while (!que.empty()) {
      const auto [t, type, mask, mi] = que.top();
      que.pop();
      if (type == 1) {
        if (t > dp1[mask][mi]) continue;
        for (int sub = mask; sub; sub = (sub - 1) & mask) {
          auto [maxTime, subK] = maskVal[sub];
          if (subK > k) continue;  // 只要能过桥，就都可以过桥
          const double useTime = maxTime * mul[mi];
          const double T = t + useTime;
          const int goMi = nextLoop(mi, useTime);
          if (sub == mask) {  // 全过去了，得到一个答案
            ans = min(ans, T);
          } else {
            // 需要选择一个人回来
            const int maskBack = mask ^ sub;
            if (T < dp2[maskBack][goMi]) {
              dp2[maskBack][goMi] = T;
              que.push({T, 2, maskBack, goMi});
            }
          }
        }
      } else {
        if (t > dp2[mask][mi]) continue;
        for (int i = 0; i < n; i++) {
          // 挑一个不在 maskBack 中的人回去
          if ((mask & (1 << i)) == 0) {
            double returnTime = time[i] * mul[mi];
            const double returnT = t + returnTime;
            const int returnMi = nextLoop(mi, returnTime);
            const int maskReturn = mask | (1 << i);
            if (returnT < dp1[maskReturn][returnMi]) {
              dp1[maskReturn][returnMi] = returnT;
              que.push({returnT, 1, maskReturn, returnMi});
            }
          }
        }
      }
    }
    // if(ans >= 1e18) return -1;

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