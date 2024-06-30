// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxHeightOfTriangle(int red, int blue) {
    int one = 0;
    int two = 0;
    for (int i = 1; i; i++) {
      if (i % 2) {
        one += i;
      } else {
        two += i;
      }
      if ((one <= red && two <= blue) || (one <= blue && two <= red)) {
        continue;
      }
      return i - 1;
    }
    return 1;
  }
};