// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> leftRigthDifference(vector<int>& nums) {
    int n = nums.size();
    vector<int> sums;
    sums.push_back(0);
    for (auto v : nums) {
      sums.push_back(v + sums.back());
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      int leftSum = sums[i - 1];
      int rightSum = sums.back() - sums[i];
      ans.push_back(abs(leftSum - rightSum));
    }
    return ans;
  }
};