#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  int Next(int v) { return (v + 1) % n; }

 public:
  bool check(vector<int>& nums) {
    n = nums.size();
    int minValPos = 0;
    for (int i = 1; i < n; i++) {
      if (nums[i - 1] > nums[i]) {
        minValPos = i;
        break;
      }
    }
    if (minValPos == 0) return true;

    for (int i = minValPos; Next(i) != minValPos; i = Next(i)) {
      if (nums[i] > nums[Next(i)]) {
        return false;
      }
    }

    return true;
  }
};