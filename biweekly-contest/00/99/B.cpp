// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
/*
1 1
2 +1*4
3 +2*4
4 +3*4

*/
class Solution {
 public:
  long long coloredCells(int n) {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += i * 4;
    }
    return ans;
  }
};
