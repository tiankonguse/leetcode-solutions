// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<ll> countKConstraintSubstrings(string s, int k,
                                        vector<vector<int>>& queries) {
    ll n = s.size();

    vector<vector<ll>> preIndex(2, vector<ll>(n + 2, n + 1));
    vector<vector<ll>> preCount(n + 2, vector<ll>(2, 0));  // 前缀 01 的个数
    vector<ll> rightBound(n + 2, n);
    vector<ll> preSum(n + 2, 0);
    vector<ll> rightIndex(n + 2, 0);

    ll h[2] = {0};
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';

      preCount[i] = preCount[i - 1];
      preCount[i][v]++;

      h[v]++;
      preIndex[v][h[v]] = i;
    }

    rightBound[0] = 0;
    rightBound[n + 1] = n + 1;
    for (int i = 1; i <= n; i++) {
      ll l0 = preCount[i - 1][0] + k + 1, l1 = preCount[i - 1][1] + k + 1;
      if (l0 < n && l1 < n) {
        ll p = max(preIndex[0][l0], preIndex[1][l1]);  // 第一个不满足的位置
        rightBound[i] = p - 1;  // 第一个满足的位置
        if (rightIndex[p-1] == 0) {
          rightIndex[p - 1] = i;  // i 的最大合法位置是 p - 1
        }
      }else{
        rightBound[i] = n;
        if (rightIndex[n] == 0) {
          rightIndex[n] = i;  // i 的最大合法位置是 p - 1
        }
      }
      preSum[i] = preSum[i - 1] + rightBound[i] - i + 1;
    }
    myprintf("rightIndex: ", "");
    for (auto v : rightIndex) {
      myprintf("%lld ", v);
    }
    myprintf("\n", "");

    ll lastVal = n + 1;
    rightIndex[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
      if (rightIndex[i] == 0) {
        rightIndex[i] = lastVal;  // i 的最大合法位置是 lastVal
      } else {
        lastVal = rightIndex[i];
      }
    }
    myprintf("    preSum: ", "");
    for (auto v : preSum) {
      myprintf("%lld ", v);
    }
    myprintf("\n", "");
    myprintf("rightBound: ", "");
    for (auto v : rightBound) {
      myprintf("%lld ", v);
    }
    myprintf("\n", "");
    myprintf("rightIndex: ", "");
    for (auto v : rightIndex) {
      myprintf("%lld ", v);
    }
    myprintf("\n", "");
    myprintf("init 2\n", "");

    vector<ll> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      ll l = q[0] + 1, r = q[1] + 1;
      ll m = r - l + 1;
      ll pr = rightIndex[r];  // 第一个不满足的位置
      myprintf("lr[%lld,%lld] pr=%lld\n", l, r, pr);
      ll sum = 0;

      if (rightBound[l] >= r) {  // // 所有的都合法
        const ll num = r - l + 1;
        sum += (1 + num) * num / 2;
      } else {
        const ll L = l;
        const ll R = pr - 1;
        myprintf("left [%lld,%lld]\n", L, R);
        sum += preSum[R] - preSum[L - 1];

        const ll num = r - pr + 1;
        sum += (1 + num) * num / 2;
      }

      ans.push_back(sum);
    }
    return ans;
  }
};