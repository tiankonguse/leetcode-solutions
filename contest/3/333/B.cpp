// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(int n) {
    int ans = 0;

    while (n) {
      int v0 = (n ^ (n - 1)) & n;
      int v1 = v0 * 2;
      if (n & v1) {  // 连续两个 1
        n += v0;
      } else {
        n -= v0;
      }
      ans++;
    }

    return ans;
  }
};
