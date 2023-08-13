// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
  bool In(int x1, int x2, int x) { return x1 < x && x < x2; }
  bool In(vector<int>& rec, int x, int y) {
    return In(rec[0], rec[2], x) && In(rec[1], rec[3], y);
  }
  bool InY(vector<int>& rec, int l, int r, int y) {
    return In(rec[1], rec[3], y) && l <= rec[0] && rec[2] <= r;
  }
  bool InX(vector<int>& rec, int b, int t, int x) {
    return In(rec[0], rec[2], x) && b <= rec[1] && rec[3] <= t;
  }
  bool In(vector<int>& rec1, vector<int>& rec2) {
    if (In(rec1, rec2[0], rec2[1])) {
      return true;  // left bottom
    }

    if (In(rec1, rec2[0], rec2[3])) {
      return true;  // left top
    }

    if (In(rec1, rec2[2], rec2[1])) {
      return true;  // right bottom
    }

    if (In(rec1, rec2[2], rec2[3])) {
      return true;  // right top
    }

    if (InY(rec1, rec2[0], rec2[2], rec2[1])) {
      return true;
    }
    if (InY(rec1, rec2[0], rec2[2], rec2[3])) {
      return true;
    }

    if (InX(rec1, rec2[1], rec2[3], rec2[0])) {
      return true;
    }
    if (InX(rec1, rec2[1], rec2[3], rec2[2])) {
      return true;
    }

    return false;
  }

 public:
  bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    if (rec1 == rec2) {
      return true;
    }
    return In(rec1, rec2) || In(rec2, rec1);
  }
};