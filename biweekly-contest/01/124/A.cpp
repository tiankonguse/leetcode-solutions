// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxOperations(vector<int>& nums) {
    int ans = 1;
    int n = nums.size();
    int sum = nums[0] + nums[1];
    for (int i = 2; i + 1 < n; i += 2) {
      if (nums[i] + nums[i + 1] == sum) {
        ans++;
      } else {
        break;
      }
    }
    return ans;
  }
};