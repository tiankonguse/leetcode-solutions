// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  double angleClock(int hour, int minutes) {
    if (hour == 12) {
      hour = 0;
    }
    double a = 360.0 * hour / 12.0 + (360.0 / 12) * minutes / 60.0;
    double b = 360.0 * minutes / 60.0;
    double c = abs(a - b);
    return min(c, 360.0 - c);
  }
};
