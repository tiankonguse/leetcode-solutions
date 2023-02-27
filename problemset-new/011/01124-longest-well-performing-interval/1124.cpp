// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int longestWPI(vector<int>& hours) {
    int n = hours.size();
    vector<int> preSums;
    preSums.reserve(n + 1);
    preSums.push_back(0);

    for (auto v : hours) {
      int sum = preSums.back();
      if (v > 8) {
        sum += 1;
      } else {
        sum -= 1;
      }
      preSums.push_back(sum);
    }

    int ans = 0;
    vector<int> sta;  // 单调队列
    unordered_map<int, int> h;
    for (int i = n; i >= 0; i--) {
      // 不选择 [0,i], 寻找最长的 [i+1, lastPos], 使得 sum[lastPos] - sum[i] > 0
      int preSum = preSums[i];
      int minSum = 1 + preSum;
      auto it = lower_bound(sta.begin(), sta.end(), minSum);
      if (it != sta.end()) {  // 找到答案
        int lastSum = *it;
        int lastPos = h[lastSum];
        ans = max(ans, lastPos - i);
      }
      if (sta.empty() || preSum > sta.back()) {
        sta.push_back(preSum);
        h[preSum] = i;
      }
    }

    return ans;
  }
};