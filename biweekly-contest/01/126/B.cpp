// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<ll> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    ll sum = 0;
    set<pair<ll, int>> h;
    for (int i = 0; i < n; i++) {
      ll v = nums[i];
      h.insert({v, i});
      sum += v;
    }

    vector<ll> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int i = q[0];
      int k = q[1];
      ll v = nums[i];
      if (v) {
        nums[i] = 0;
        sum -= v;
        h.erase({v, i});
      }

      while (k > 0 && !h.empty()) {
        k--;
        auto [v, i] = *h.begin();
        nums[i] = 0;
        sum -= v;
        h.erase(h.begin());
      }
      ans.push_back(sum);
    }
    return ans;
  }
};