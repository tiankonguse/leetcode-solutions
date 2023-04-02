// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
    // [0, n-1)
    set<int> dp[2], block;

    for (auto v : banned) {
      block.insert(v);
    }

    for (int i = 0; i < n; i++) {
      if (block.count(i)) continue;
      if (i == p) continue;
      dp[i % 2].insert(i);
    }

    vector<int> ans(n, -1);
    queue<int> que;
    ans[p] = 0;
    que.push(p);

    while (!que.empty()) {
      int p = que.front();
      que.pop();

      int L = p - k + 1, R = p + k - 1;
      if (L < 0) L = (k - 1) - p;
      if (R >= n) R = (k - 1) - (p - (n - k)) + (n - k);

      int flag = p % 2;
      if (k % 2 == 1) {  // 在同奇偶 set 查找
      } else {           // 在异奇偶 set 查找
        flag = 1 - flag;
      }

      auto& s = dp[flag];
      auto it = s.lower_bound(L);
      while (it != s.end()) {
        int v = *it;
        if (v > R) break;

        ans[v] = ans[p] + 1;
        que.push(v);
        s.erase(it++);
      }
    }

    return ans;
  }
};