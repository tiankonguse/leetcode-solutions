// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumLength(vector<int>& nums) {
    unordered_map<int, int> h;
    unordered_map<int, int> pre;
    for (auto v : nums) {
      h[v]++;
      if (h[v] == 1) {
        int vv = sqrt(v * 1.0);
        if (vv * vv == v) {
          pre[v] = vv;
        } else {
          pre[v] = -1;
        }
      }
    }

    int ans = 1;
    for (auto [k, v] : h) {
      // 以 k 为 x^k
      if (k == 1) {
        if (v % 2 == 0) {
          ans = max(ans, v - 1);
        } else {
          ans = max(ans, v);
        }
        continue;
      }
      int tmp = 1;
      int p = pre[k];
      while (p != -1 && h.count(p) && h[p] >= 2) {
        tmp += 2;
        p = pre[p];
      }
      ans = max(ans, tmp);
    }
    return ans;
  }
};