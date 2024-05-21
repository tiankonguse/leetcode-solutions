// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    int m = queries.size();
    vector<bool> ans(m, true);
    set<int> h;
    for (int i = 0; i + 1 < n; i++) {
      int a = nums[i];
      int b = nums[i + 1];
      if (a % 2 == b % 2) {
        h.insert(i);
      }
    }

    for (int i = 0; i < m; i++) {
      int from = queries[i][0];
      int to = queries[i][1];
      if (from == to) {
        continue;
      }
      
      auto it = h.lower_bound(from);
      if (it == h.end()) {
        continue;
      }
      if (*it >= to) {
        continue;
      }
      ans[i] = false;
    }
    return ans;
  }
};