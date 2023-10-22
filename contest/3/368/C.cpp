// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  unordered_map<int, int> H;  // 每个次数出现的次数
  int Solver(int a) {         // 分为 [a, a+1] 组
    int ans = 0;
    for (auto [k, v] : H) {
      if (k < a) return -1;
      int b = k / (a + 1);
      int c = k % (a + 1);
      if (c == 0) {
        ans += b * v;
        continue;
      }
      const int left = a - c;
      if (left > b) return -1;
      ans += (b + 1) * v;
    }

    return ans;
  }

 public:
  int minGroupsForValidAssignment(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> h;  // 每个值出现的次数
    for (auto v : nums) {
      h[v]++;
    }

    int V = 0;
    for (auto [k, v] : h) {
      H[v]++;
      V = max(V, v);
    }

    int ans = n;
    for (int i = 1; i <= V; i++) {
      int v = Solver(i);
      if (v != -1) {
        ans = min(ans, v);
      }
    }
    return ans;
  }
};