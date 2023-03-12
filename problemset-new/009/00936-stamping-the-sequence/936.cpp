// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int sn, tn;
  vector<vector<int>> dp;
  string s, t;
  vector<vector<int>> batchs;

  bool Dfs(int si, int ti, int flag = true) {
    int& ret = dp[si][ti];
    if (ret != -1) return ret;  // 只能是 false

    if (s[si] != t[ti]) return ret = 0;
    // 至少匹配一个
    si++;
    ti++;

    if (si == sn) {    // stamp 匹配结束
      if (ti == tn) {  // 找到一组答案
        batchs.push_back(vector<int>());
        return ret = 1;
      }

      for (int i = 0; i < sn; i++) {  // 下一个重新开始匹配
        if (Dfs(i, ti, true)) {
          batchs.back().push_back(ti - i);
          batchs.push_back(vector<int>());
          return ret = 1;
        }
      }
      return ret = 0;
    }

    if (ti == tn) {  // stamp 没结束，target 结束
      return ret = 0;
    }

    // 一种方案是继续匹配
    if (Dfs(si, ti, false)) {
      return ret = 1;
    }

    // 或者追增新的 stamp
    if (Dfs(0, ti, false)) {
      batchs.back().push_back(ti);
      return ret = 1;
    }
    return ret = 0;
  }

 public:
  vector<int> movesToStamp(string stamp, string target) {
    s.swap(stamp);
    t.swap(target);
    sn = s.size();
    tn = t.size();
    dp.resize(sn, vector<int>(tn, -1));

    vector<int> ans;
    if (Dfs(0, 0)) {
      batchs.back().push_back(0);
      for (auto& b : batchs) {
        std::reverse(b.begin(), b.end());
        for (auto v : b) {
          ans.push_back(v);
        }
      }
    }
    return ans;
  }
};