// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minAbsoluteDifference(vector<int>& nums, int x) {
    map<int, int> m;
    int n = nums.size();
    for (int i = x; i < n; i++) {
      m[nums[i]]++;
    }

    int ans = abs(nums.front() - nums.back());
    for (int i = 0; i + x < n; i++) {
      int v = nums[i];
      if (m.size() == 0) continue;
      auto it = m.lower_bound(v);
      if (it != m.end()) {
        ans = min(ans, abs(v - it->first));
      }
      if (it != m.begin()) {
        it--;
        ans = min(ans, abs(v - it->first));
      }

      int V = nums[i + x];
      m[V]--;
      if (m[V] == 0) {
        m.erase(V);
      }
    }
    return ans;
  }
};