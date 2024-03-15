// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    set<int> s(arr2.begin(), arr2.end());

    int ans = 0;
    for (auto v : arr1) {
      int l = v - d;
      int r = v + d;
      auto it = s.lower_bound(l);
      if (it == s.end() || *it > r) {
        ans++;
      }
    }

    return ans;
  }
};