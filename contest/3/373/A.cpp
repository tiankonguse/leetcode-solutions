// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool areSimilar(vector<vector<int>>& mat, int k) {
    int n = mat.size();
    int m = mat[0].size();
    k = k % m;
    if (k == 0) return true;

    bool flag = true;
    for (auto& line : mat) {
      int K = k;    // 奇数行
      if (!flag) {  // 偶数行
        K = m - k;
      }

      for (int i = 0; i < m; i++) {
        if (line[i] != line[(i + K) % m]) {
          return false;
        }
      }

      flag = !flag;
    }
    
    return true;
  }
};