// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0xf3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  int W(vector<vector<int>>& boxes, int p) {
    return p > 0 ? boxes[p - 1][1] : 0;
  }
  int P(vector<vector<int>>& boxes, int p) {
    return p > 0 ? boxes[p - 1][0] : -1;
  }

 public:
  int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes,
                    int maxWeight) {
    int n = boxes.size();
    int weight = 0;
    int count = 0;
    int lastPort = -1;
    int lasrPos = 0;

    vector<int> dp(n + 1, inf);
    dp[0] = 0;

    for (int l = 1, r = 0; l <= n; l++) {
      // find the longest valid window [l:r]
      while (r + 1 <= n && r + 1 - l + 1 <= maxBoxes &&
             weight + W(boxes, r + 1) <= maxWeight) {
        r++;
        weight += W(boxes, r);
        if (P(boxes, r) != P(boxes, r - 1)) count++;
        if (P(boxes, r) != lastPort) {
          lastPort = P(boxes, r);
          lasrPos = r;
        }
      }

      // update dp[r] = dp[l+1] + f(l, r)
      dp[r] = min(dp[r], dp[l - 1] + count + 1);

      // update dp[lasrPos-1], where [lasrPos:r] share the same port
      if (l < lasrPos) {
        dp[lasrPos - 1] = min(dp[lasrPos - 1], dp[l - 1] + count);
      }

      weight -= W(boxes, l);
      if (l + 1 <= n && P(boxes, l) != P(boxes, l + 1)) {
        count--;
      }
    }
    return dp[n];
  }
};
