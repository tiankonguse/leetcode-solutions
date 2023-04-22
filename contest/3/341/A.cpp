// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
    int line = -1, num = -1;
    int n = mat.size();
    for (int i = 0; i < n; i++) {
      ll sum = accumulate(mat[i].begin(), mat[i].end(), 0ll);
      if (sum > num) {
        num = sum;
        line = i;
      }
    }
    return {line, num};
  }
};