// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<ll> countKConstraintSubstrings(string s, int k,
                                        vector<vector<int>>& queries) {
    vector<ll> ans;
    ans.reserve(queries.size());
    ll n = s.size();

    vector<vector<ll>> preIndex(2, vector<ll>(n + 2, n + 1));
    vector<vector<ll>> preCount(n + 2, vector<ll>(2, 0));  // 前缀 01 的个数
    vector<ll> rightBound(n + 2, n);
    vector<ll> preSum(n + 2, 0);

    myprintf("begin\n", "");
    ll h[2] = {0};
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';

      preCount[i] = preCount[i - 1];
      preCount[i][v]++;

      h[v]++;
      preIndex[v][h[v]] = i;
    }
    myprintf("init 1\n", "");

    rightBound[0] = 0;
    rightBound[n + 1] = n + 1;
    for (int i = 1; i <= n; i++) {
      ll l0 = preCount[i - 1][0] + k + 1, l1 = preCount[i - 1][1] + k + 1;
      if (l0 < n && l1 < n) {
        ll p = max(preIndex[0][l0], preIndex[1][l1]);  // 第一个不满足的位置
        rightBound[i] = p - 1;  // 第一个满足的位置
      }
      preSum[i] = preSum[i - 1] + rightBound[i];
    }
    myprintf("rightBound: ", "");
    for (auto v : rightBound) {
      myprintf("%lld ", v);
    }
    myprintf("\n", "");
    myprintf("init 2\n", "");

    for (auto& q : queries) {
      const ll l = q[0] + 1, r = q[1] + 1;
      const ll p =
          std::upper_bound(rightBound.begin() + l, rightBound.end(), r) -
          rightBound.begin();  // 第一个不满足的位置
      myprintf("lr[%lld,%lld] p=%lld\n", l, r, p);
      ll sum = 0;

      const ll L = l;
      const ll R = min(p - 1, r);
      myprintf("left [%lld,%lld]\n", L, R);
      sum += preSum[R] - preSum[L - 1] - (L - 1 + R - 1) * (R - L + 1) / 2;

      if (p <= r) {
        const ll num = r - p + 1;
        sum += (1 + num) * num / 2;
      }
      ans.push_back(sum);
    }
    return ans;
  }
};