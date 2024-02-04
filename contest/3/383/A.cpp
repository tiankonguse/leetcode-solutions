// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int returnToBoundaryCount(vector<int>& nums) {
    int ans = 0;
    int pos = 0;
    for (auto v : nums) {
      pos += v;
      if (pos == 0) {
        ans++;
      }
    }
    return ans;
  }
};