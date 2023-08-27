// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumSum(int n, int k) {
    int l = k / 2;
    if (l >= n) {
      return (1 + n) * n / 2;
    }

    int ans = 0;
    ans += (1 + l) * l / 2;
    // printf("add (%d,%d)\n", 1, l);

    int r = k + (n - l) - 1;
    l = k;
    // printf("add (%d,%d)\n", l, r);
    ans += (l + r) * (r - l + 1) / 2;
    return ans;
  }
};
