// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes,
                    int maxWeight) {
    int n = boxes.size();
    int weight = boxes[0][1];
    int count = 2;

    vector<int> dp(n + 1);
    dp[1] = 2;
    for (int r = 1, l = 0; r < n; r++) {
      if (boxes[r][0] != boxes[r - 1][0]) {
        count++;
      }
      weight += boxes[r][1];

     // 
      while (r - l + 1 > maxBoxes || weight > maxWeight || dp[l] == dp[l + 1]) {
        weight -= boxes[l][1];
        l++;
        if (boxes[l][0] != boxes[l - 1][0]) {
          count--;
        }
      }

      dp[r + 1] = dp[l] + count;
    }
    return dp[n];
  }
};
