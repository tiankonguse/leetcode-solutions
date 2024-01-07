// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> h1;
    for (auto v : nums1) {
      h1[v] = 0;
    }
    unordered_map<int, int> h2;
    for (auto v : nums2) {
      h2[v] = 0;
    }

    int ans = 0;
    int n2 = nums1.size() / 2;

    int use1 = 0;
    for (auto& [k, v] : h1) {
      if (h2.count(k) == 0) {
        ans++;
        use1++;
        v = 1;
      }
      if (use1 >= n2) {
        break;
      }
    }

    int use2 = 0;
    for (auto& [k, v] : h2) {
      if (h2.count(k) == 0) {
        ans++;
        use2++;
        v = 1;
      }
      if (use2 >= n2) {
        break;
      }
    }

    if (use1 < n2) {
      for (auto& [k, v] : h1) {
        if (v == 1) continue;
        ans++;
        use1++;
        v = 1;
        if (h2.count(k)) {
          h2[k] = 1;
        }
        if (use1 >= n2) {
          break;
        }
      }
    }

    if (use2 < n2) {
      for (auto& [k, v] : h2) {
        if (v == 1) continue;
        ans++;
        use2++;
        v = 1;
        if (use2 >= n2) {
          break;
        }
      }
    }

    return ans;
  }
};