#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    int K = -1;
    for (int i = 0; i < n; i++) {
      if (nums[i] == k) K = i;
    }
    unordered_map<int, int> m;
    m[0] = 1;  // 只选自己

    int l = 0, r = 0;
    for (int i = K - 1; i >= 0; i--) {
      int c = nums[i];
      if (c < k) {
        l++;
      } else {
        r++;
      }
      m[l - r]++;
    }

    // 选择k 的所有前缀
    int ans = 0;
    if (m.count(0)) ans += m[0];
    if (m.count(-1)) ans += m[-1];

    l = 0, r = 0;
    for (int i = K + 1; i < n; i++) {
      int c = nums[i];
      if (c < k) {
        l++;
      } else {
        r++;
      }
      int d = l - r;
      if (m.count(-d)) ans += m[-d];
      if (m.count(-d - 1)) ans += m[-d - 1];
    }
    return ans;
  }
};
