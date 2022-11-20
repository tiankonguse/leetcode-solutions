#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int unequalTriplets(vector<int>& nums) {
    int ans = 0;
    for (auto a : nums) {
      for (auto b : nums) {
        for (auto c : nums) {
          if (a != b && a != c && b != c) {
            ans++;
          }
        }
      }
    }
    return ans/6;
  }
};