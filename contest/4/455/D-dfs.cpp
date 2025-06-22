
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
  vector<vector<double>> dp1, dp2;
  int MASK;
  vector<int> time;
  vector<double> mul;
  int n, m, k;
  // __builtin_popcount 一的个数

  int nextLoop(const int mi, double useTime) {
    // 时间向下取整
    return (mi + int(floor(useTime))) % m;
  }

  // mask, 未过桥的人，此函数需要从未过桥的人中选不超过 k 个人来过桥
  double Dfs1(const int mask, const int mi) {
    double& ret = dp1[mask][mi];
    if (ret >= 0) return ret;
    if (mask == 0) return ret = 0;
    MyPrintf("Dfs1 inter: mask = %d, mi = %d\n", mask, mi);
    ret = 1e18;
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
      int subK = __builtin_popcount(sub);
      if (subK > k) continue;  // 只要能过桥，就都可以过桥
      int maxTime = 0;
      for (int i = 0; i < n; i++) {
        if (sub & (1 << i)) {
          maxTime = max(maxTime, time[i]);
        }
      }
      double useTime = maxTime * mul[mi];
      MyPrintf("Dfs1->Dfs2 before mask = %d, mi = %d, sub = %d, maxTime=%d mul=%f useTime = %f\n", mask, mi, sub,
               maxTime, mul[mi], useTime);
      double childTime = Dfs2(mask ^ sub, nextLoop(mi, useTime));

      MyPrintf("Dfs1->Dfs2 after mask = %d, mi = %d, sub = %d, useTime = %f, childTime = %f tmpAns=%f\n", mask, mi, sub,
               useTime, childTime, useTime + childTime);
      ret = min(ret, useTime + childTime);
    }

    MyPrintf("Dfs1 ans: mask = %d, mi = %d, ret = %f\n", mask, mi, ret);
    return ret;
  }

  // mask 未过桥的人，需要已过桥中挑一个人返回，变成未过桥的人
  double Dfs2(const int mask, const int mi) {
    double& ret = dp2[mask][mi];
    if (ret >= 0) return ret;
    if (mask == 0) return ret = 0;
    MyPrintf("Dfs2 inter: mask = %d, mi = %d\n", mask, mi);
    ret = 1e18;
    for (int i = 0; i < n; i++) {
      // 挑一个不在 mask 中的人回去
      if ((mask & (1 << i)) == 0) {
          double useTime = time[i] * mul[mi];
          MyPrintf("Dfs2->Dfs1 befor mask = %d, mi = %d, i = %d, useTime = %f\n", mask, mi, i, useTime);
          double childTime = Dfs1(mask | (1 << i), nextLoop(mi, useTime));
          MyPrintf("Dfs2->Dfs1 after mask = %d, mi = %d, i = %d, useTime = %f, childTime = %f tmpAns=%f\n", mask, mi, i,
                   useTime, childTime, useTime + childTime);
          ret = min(ret, useTime + childTime);
        }
    }
    MyPrintf("Dfs2 ans: mask = %d, mi = %d, ret = %f\n", mask, mi, ret);
    return ret;
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
    dp1.resize(MASK, vector<double>(m, -1));
    dp2.resize(MASK, vector<double>(m, -1));
    return Dfs1(MASK - 1, 0);
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