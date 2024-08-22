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

    vector<ll> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int l = q[0], r = q[1];
      ll sum = 0;
      for (int i = l; i <= r; i++) {
        int dp[2] = {0, 0};
        for (int j = i; j <= r; j++) {
          dp[s[j] - '0']++;
          if (dp[0] <= k || dp[1] <= k) {
            sum++;
          } else {
            break;
          }
        }
      }
      ans.push_back(sum);
    }
    return ans;
  }
};