// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int distanceTraveled(int mainTank, int additionalTank) {
    int ans = 0;
    while (mainTank >= 5 && additionalTank > 0) {
      ans += 50;
      mainTank -= 5;
      additionalTank -= 1;
        mainTank += 1;
    }
    ans += mainTank * 10;

    return ans;
  }
};