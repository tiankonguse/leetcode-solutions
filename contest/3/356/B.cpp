// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countCompleteSubarrays(vector<int>& nums) {
    int ans = 0;
    unordered_set<int> h(nums.begin(), nums.end());
    int baseNum = h.size();

    int n = nums.size();
    for (int i = 0; i < n; i++) {
      h.clear();
      for (int j = i; j < n; j++) {
        h.insert(nums[j]);
        if (h.size() == baseNum) {
          ans += n - j;
          break;
        }
      }
    }

    return ans;
  }
};
