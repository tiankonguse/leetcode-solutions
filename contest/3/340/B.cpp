// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<ll> distance(vector<int>& nums) {
    int n = nums.size();
    vector<ll> ans(n, 0);
    unordered_map<int, vector<int>> h;
    for (int i = 0; i < n; i++) {
      int v = nums[i];
      h[v].push_back(i);
    }

    for (auto& [v, ps] : h) {
      if (ps.size() == 1) {
        continue;
      }

      ll preSum = 0, subSum = 0;
      for (int p : ps) {
        subSum += p;
      }

      ll l = 0, r = ps.size();
      for (int p : ps) {
        ll tmp = 0;
        tmp += l * p - preSum;
        tmp += subSum - r * p;
        ans[p] = tmp;

        l++;
        preSum += p;
        r--;
        subSum -= p;
      }
    }

    return ans;
  }
};
