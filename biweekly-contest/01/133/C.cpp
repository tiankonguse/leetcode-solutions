// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (auto v : nums) {
      if ((ans&1) ^ v) continue;
      ans++;
    }
    return ans;
  }
};