// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> countVisitedNodes(vector<int>& g) {
    int n = g.size();

    vector<int> ans(n);

    vector<int> sta;
    sta.reserve(n);
    for (int i = 0; i < n; i++) {
      if (ans[i]) continue;

      int index = -1;
      int s = i;
      while (ans[s] == 0) {
        ans[s] = index;
        index--;
        sta.push_back(s);
        s = g[s];
      }

      if (ans[s] > 0) {  // 旧环，当前栈中是一条链
        while (!sta.empty()) {
          ans[sta.back()] = ans[g[sta.back()]] + 1;
          sta.pop_back();
        }
      } else {  // 新环
        int firstIndex = ans[s];
        int len = firstIndex - index;

        while (!sta.empty()) {
          if (ans[sta.back()] <= firstIndex) {
            ans[sta.back()] = len;
          } else {
            ans[sta.back()] = ans[g[sta.back()]] + 1;
          }
          sta.pop_back();
        }
      }
    }

    return ans;
  }
};
