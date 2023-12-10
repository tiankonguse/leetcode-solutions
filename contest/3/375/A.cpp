// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countTestedDevices(vector<int>& batteryPercentages) {
    int ans = 0;
    for (auto v : batteryPercentages) {
      if (v > ans) {
        ans++;
      }
    }
    return ans;
  }
};