// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
    sort(nums.begin(), nums.end());
    map<ll, ll> m;
    unordered_map<ll, ll> counts;

    ll maxVal = nums.back();
    for (ll v : queries) {
      counts[v] = 0;
      m[v] = -1;
      maxVal = max(maxVal, v);
    }

    ll sum = 0;
    for (auto v : nums) {
      counts[v]++;
      m[v] = -1;
      sum += v;  // 全部设置为 0
    }

    ll pre = 0;
    ll x = 0, y = nums.size();
    for (auto& [k, v] : m) {  // 全部设置为 v
      ll dis = k - pre;
      sum = sum - y * dis + x * dis;
      x += counts[k];
      y -= counts[k];
      v = sum;
      pre = k;
    }

    vector<long long> ans;
    ans.reserve(queries.size());
    for (auto v : queries) {
      ans.push_back(m[v]);
    }

    return ans;
  }
};