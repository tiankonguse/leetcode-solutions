// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumCount(vector<int>& nums) {
    int a = 0, b = 0;
    for (auto v : nums) {
      if (v < 0) a++;
      if (v > 0) b++;
    }
    return max(a, b);
  }
};
