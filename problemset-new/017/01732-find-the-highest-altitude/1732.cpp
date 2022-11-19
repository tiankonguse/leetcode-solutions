
#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int largestAltitude(vector<int>& gain) {
    int ans = 0;
    int pre = 0;
    for (auto v : gain) {
      pre += v;
      ans = max(ans, pre);
    }
    return ans;
  }
};
