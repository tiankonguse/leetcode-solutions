// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<int> getSneakyNumbers(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int p = i;
      while (nums[p] != p) {
        int pp = nums[p];
        if (nums[pp] == pp) {  // 目标位置已经是目标值了
          break;
        }
        swap(nums[p], nums[pp]);
      }
    }
    for (int i = 0; i < n; i++) {
      if (i != nums[i]) {
        ans.push_back(nums[i]);
      }
    }
    return ans;
  }
};