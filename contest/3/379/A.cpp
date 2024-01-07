// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
    int cc = 0;
    int ans = 0;
    for (auto& d : dimensions) {
      int a = d[0];
      int b = d[1];
      int CC = a * a + b * b;
      if (CC > cc || (CC == cc && a * b > ans)) {
        cc = CC;
        ans = a * b;
      }
    }
    return ans;
  }
};