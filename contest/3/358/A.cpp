// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxSum(vector<int>& nums) {
    vector<vector<int>> bits(10);
    auto HighNum = [](int v) -> int {
      int ans = v % 10;
      while (v) {
        ans = max(ans, v % 10);
        v /= 10;
      }
      return ans;
    };
    for (auto v : nums) {
      bits[HighNum(v)].push_back(v);
    }

    int ans = -1;
    for (auto& vs : bits) {
      if (vs.size() >= 2) {
        sort(vs.begin(), vs.end(), [](int a, int b) { return a > b; });
        ans = max(ans, vs[0] + vs[1]);
      }
    }
    return ans;
  }
};
