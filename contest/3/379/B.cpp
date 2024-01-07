// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
    // 最多两步， 最少1步骤

    // 车垂直
    if (a == e) {
      if (c != a) {
        return 1;
      }
      if (b < f) {
        if (d < b || d > f) {
          return 1;
        }
      } else {  // b > f
        if (d > b || d < f) {
          return 1;
        }
      }
    }
    // 车水平
    if (b == f) {
      if (d != b) {
        return 1;
      }
      if (a < e) {
        if (c < a || c > e) {
          return 1;
        }
      } else {  // a> e
        if (c > a || c < e) {
          return 1;
        }
      }
    }
    // 象斜着
    int ae = abs(a - e);
    int bf = abs(b - f);
    int ce = abs(c - e);
    int df = abs(d - f);
    int ac = abs(a - c);
    int bd = abs(b - d);

    if (ce == df) {
      if (ac != bd) return 1;
      if (ae != bf) return 1;
      if (ac + ae != ce) return 1;
      if (bd + bf != df) return 1;
    }
    return 2;
  }
};