// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int differenceOfSum(vector<int>& nums) {
    int a = 0, b = 0;
    for (auto v : nums) {
      a += v;
      while (v) {
        b += v % 10;
        v /= 10;
      }
    }
    return abs(a - b);
  }
};