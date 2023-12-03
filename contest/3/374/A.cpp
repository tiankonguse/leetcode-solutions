// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> findPeaks(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size();
    for (int i = 1; i + 1 < n; i++) {
      if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};