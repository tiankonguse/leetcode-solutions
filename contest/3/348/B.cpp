// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int semiOrderedPermutation(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = n - 1; i > 0; i--) {
      if (nums[i] == 1) {
        swap(nums[i], nums[i - 1]);
        ans++;
      }
    }

    for (int i = 0; i < n - 1; i++) {
      if (nums[i] == n) {
        swap(nums[i], nums[i + 1]);
        ans++;
      }
    }
    return ans;
  }
};