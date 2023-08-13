// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    // 令第一个矩阵偏左
    if(rec1[0] > rec2[0])swap(rec1, rec2);
    if(rec1[2] <= rec2[0]) return false; // 垂直方向没有交集

    if(rec1[1] > rec2[1])swap(rec1, rec2);
    if(rec1[3] <= rec2[1]) return false; // 水平方向没有交集

    return true;
  }
};