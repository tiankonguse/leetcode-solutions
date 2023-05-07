// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> distinctDifferenceArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> pre(n + 1, 0), suf(n + 1, 0);
    unordered_set<int> l, r;
    for (int i = 0; i < n; i++) {
      l.insert(nums[i]);
      pre[i] = l.size();
    }
    for (int i = n - 1; i >= 0; i--) {
      r.insert(nums[i]);
      suf[i] = r.size();
    }

    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
      ans[i] = pre[i] - suf[i + 1];
    }
    return ans;
  }
};