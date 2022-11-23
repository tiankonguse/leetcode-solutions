#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int countBalls(int lowLimit, int highLimit) {
    unordered_map<int, int> m;

    int ans = 0;
    for (int i = lowLimit; i <= highLimit; i++) {
      int sum = 0;
      int tmp = i;
      while (tmp) {
        sum += tmp % 10;
        tmp /= 10;
      }

      m[sum]++;
      ans = max(ans, m[sum]);
    }

    return ans;
  }
};