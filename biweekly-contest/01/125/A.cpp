// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(vector<int>& nums, int k) {
    int ans = 0;
    for (auto v : nums) {
      if (v < k) {
        ans++;
      }
    }
    return ans;
  }
};