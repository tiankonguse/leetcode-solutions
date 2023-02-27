// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> mergeArrays(vector<vector<int>>& nums1,
                                  vector<vector<int>>& nums2) {
    map<int, int> m;
    for (auto& v : nums2) {
      m[v[0]] += v[1];
    }
    for (auto& v : nums1) {
      m[v[0]] += v[1];
    }
    vector<vector<int>> ans;
    for (auto [k, v] : m) {
      ans.push_back({k, v});
    }
    return ans;
  }
};