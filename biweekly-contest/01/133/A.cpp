// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumOperations(vector<int>& nums) {
    int ans = 0;
    vector<int> h = {0, 1, 1};
    for (auto v : nums) {
      ans += h[v % 3];
    }
    return ans;
  }
};