// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
      if (a[0] != b[0]) {
        return a[0] < b[0];
      }
      return a[1] > b[1];
    });

    int ans = 0;

    int a = -1, b = -1;

    for (auto& v : intervals) {
      int x = v[0], y = v[1];
      if (a <= x && y <= b) {
        continue;
      }
      a = x, b = y;
      ans++;
    }

    return ans;
  }
};
