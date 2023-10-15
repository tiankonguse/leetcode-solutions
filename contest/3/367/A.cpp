// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> findIndices(vector<int>& nums, int indexDifference,
                          int valueDifference) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (abs(i - j) >= indexDifference &&
            abs(nums[i] - nums[j]) >= valueDifference) {
          return {i, j};
        }
      }
    }
    return {-1, -1};
  }
};