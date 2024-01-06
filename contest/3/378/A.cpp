// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool hasTrailingZeros(vector<int>& nums) {
    int num = 0;
    for (auto v : nums) {
      if (v % 2 == 0) {
        num++;
        if (num >= 2) return true;
      }
    }
    return false;
  }
};