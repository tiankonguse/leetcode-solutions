// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    int x = abs(sx - fx);
    int y = abs(sy - fy);

    if (x == 0 && y == 0 && t == 1) {
      return false;
    }

    return max(x, y) <= t;
  }
};