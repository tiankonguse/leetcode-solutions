// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> resultArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    int l = 0, r = n - 1;
    for (auto v : nums) {
      if (l == 0) {
        ans[l++] = v;
      } else if (r == n - 1) {
        ans[r--] = v;
      } else {
        if (ans[l - 1] > ans[r + 1]) {
          ans[l++] = v;
        } else {
          ans[r--] = v;
        }
      }
    }
    std::reverse(ans.begin() + l, ans.end());
    return ans;
  }
};