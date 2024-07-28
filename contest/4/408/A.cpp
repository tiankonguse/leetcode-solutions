// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool canAliceWin(vector<int>& nums) {
    int sum = 0;
    for (auto v : nums) {
      if (v >= 10) {
        sum += v;
      } else {
        sum -= v;
      }
    }
    return sum != 0;
  }
};