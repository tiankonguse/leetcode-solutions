#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int secondHighest(const string& s) {
    int nums[3] = {-1, -1, -1};
    for (auto c : s) {
      if (c < '0' || c > '9') continue;
      nums[2] = c - '0';
      if (nums[0] == nums[2] || nums[1] == nums[2]) continue;

      for (int i = 2; i > 0; i--) {
        if (nums[i] > nums[i - 1]) {
          swap(nums[i], nums[i - 1]);
        }
      }
    }
    return nums[1];
  }
};
