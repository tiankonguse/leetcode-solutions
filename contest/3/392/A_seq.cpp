// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Solver(vector<int>& nums) {
    map<int, int> h;
    h[100] = 1;
    int ans = 0;
    for (auto v : nums) {
      auto it = h.lower_bound(v);
      if (it == h.begin()) { // 不存在比 v 小的元素
        h[v] = max(h[v], 1);
      } else {
        it--;
        h[v] = max(h[v], it->second + 1);
        printf("v=%d, ans=%d pre={%d,%d}\n", v, h[v], it->first, it->second);
      }
      ans = max(ans, h[v]);
    }
    return ans;
  }

 public:
  int longestMonotonicSubarray(vector<int>& nums) {
    int ans = 1;
    ans = max(ans, Solver(nums));
    std::reverse(nums.begin(), nums.end());
    ans = max(ans, Solver(nums));
    return ans;
  }
};