// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> findMatrix(vector<int>& nums) {
    unordered_map<int, int> m;

    int maxNum = 0;
    for (auto v : nums) {
      m[v]++;
      maxNum = max(maxNum, m[v]);
    }

    vector<vector<int>> ans(maxNum);
    for (auto [v, num] : m) {
      for (int i = 0; i < num; i++) {
        ans[i].push_back(v);
      }
    }
    return ans;
  }
};