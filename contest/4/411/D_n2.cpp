// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

// 超出时间限制 620 / 627 个通过的测试用例
typedef long long ll;
class Solution {
 public:
  vector<ll> countKConstraintSubstrings(const string& s, int k,
                                        vector<vector<int>>& queries) {
    int n = s.size();

    // map<ll, ll> H[2];  // 01 数量到位置的映射
    vector<vector<ll>> preIndex(2, vector<ll>(n + 2, n + 1));
    vector<vector<ll>> preCount(n + 2, vector<ll>(2, 0));  // 前缀 01 的个数

    ll h[2] = {0};
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - '0';

      preCount[i] = preCount[i - 1];
      preCount[i][v]++;

      h[v]++;
      // H[v].insert({h[v], i});
      preIndex[v][h[v]] = i;
    }

    vector<ll> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int l = q[0] + 1, r = q[1] + 1;
      ll m = r - l + 1;
      // 所有子串 - 01都大于k的子串
      ll sum = (1 + m) * m / 2;

      for (int i = l; i <= r; i++) {
        ll l0 = preCount[i - 1][0] + k + 1, l1 = preCount[i - 1][1] + k + 1;
        if (l0 > n || l1 > n) continue;  // 越界了，不存在

        ll kk = max(preIndex[0][l0], preIndex[1][l1]);
        if (kk > r) continue;
        sum -= r - kk + 1;
      }
      ans.push_back(sum);
    }
    return ans;
  }
};