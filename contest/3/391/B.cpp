// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxBottlesDrunk(int n, int k) {
    int ans = 0;
    while (n >= k) {
      ans += k;
      n = n - k + 1;
      k++;
    }
    ans += n;
    return ans;
  }
};