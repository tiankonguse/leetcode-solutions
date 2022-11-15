#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    sort(boxTypes.begin(), boxTypes.end(),
         [](auto& a, auto& b) { return a[1] > b[1]; });
    int ans = 0;

    for (auto& v : boxTypes) {
      if (truckSize > v[0]) {
        ans += v[0] * v[1];
        truckSize -= v[0];
      } else {
        ans += truckSize * v[1];
        truckSize = 0;
        break;
      }
    }
    return ans;
  }
};