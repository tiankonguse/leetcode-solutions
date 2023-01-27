// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  int maxSatisfaction(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    int sum = 0;
    for (auto v : nums) {
      sum += v;
    }

    int ans = 0;

    int tmp = 0;
    for (int i = 0; i < n; i++) {
      tmp += (i + 1) * nums[i];
    }
    ans = max(ans, tmp);

    for (int i = 0; i < n; i++) {
      tmp -= sum;
      ans = max(ans, tmp);
      sum -= nums[i];
    }
    return ans;
  }
};