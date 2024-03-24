// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(int k) {
    int ans = k;
    for (int i = 1; i <= k; i++) {
      // 最大值时 i
      int one = i - 1;
      int two = (k + i - 1) / i - 1;
        // printf("i=%d ans=%d\n", i, one+two);
      ans = min(ans, one + two);
    }
    return ans;
  }
};