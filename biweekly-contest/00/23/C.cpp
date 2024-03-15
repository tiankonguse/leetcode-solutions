// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Check(int r, int x1, int y1, int y2) {
    if (y1 >= 0) {
      return r * r >= x1 * x1 + y1 * y1;
    } else if (y2 <= 0) {
      return r * r >= x1 * x1 + y2 * y2;
    } else {
      return r * r >= x1 * x1;
    }
  }

 public:
  bool checkOverlap(int r, int x, int y, int x1, int y1, int x2, int y2) {
    // 转化圆心到原点
    x1 -= x;
    x2 -= x;
    y1 -= y;
    y2 -= y;

    // 圆在矩阵内
    if (x1 <= 0 && x2 >= 0 && y1 <= 0 && y2 >= 0) {
      return true;
    }

    return Check(r, x1, y1, y2) || Check(r, x2, y1, y2) ||
           Check(r, y1, x1, x2) || Check(r, y2, x1, x2);
  }
};
