// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minAnagramLength(const string& s) {
    int n = s.length();
    vector<vector<int>> pre(n + 1, vector<int>(26, 0));
    vector<int> base(26, 0);
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - 'a';
      base[v]++;
      pre[i] = base;
    }

    auto Check = [&pre](const int t) -> bool {
      int n = pre.size();
      auto& base = pre[t];
      for (int i = t+t; i < n; i+=t) {
        int k = 0;
        for (int j = 0; j < 26; j++) {
          int one = base[j], sum = pre[i][j];
          if (sum == 0) continue;
          if (one == 0) {
              // printf("one == 0, i=%d j=%d\n", i, j);
              return false;        // 不存在的字符
          }
          if (sum % one != 0) {
              // printf("sum % one != 0, i=%d j=%d sum=%d one=%d\n", i, j, sum, one);
              return false;        // 不存在的字符
          }
          if (k == 0) {
            k = sum / one;
          } else {
            if (sum / one != k){
              // printf("sum / one != k, i=%d j=%d sum=%d one=%d, sum/one=%d k=%d\n", i, j, sum, one, sum/one, k);
              return false;        // 不存在的字符
            } 
          }
        }
      }
      return true;
    };

    for (int i = 1; i < n; i++) {
      if (n % i != 0) continue;
      if (Check(i)) {
          // printf("n=%d i=%d true\n", n, i); 
          return i;
      }
      // printf("n=%d i=%d false\n", n, i);
    }
    return n;
  }
};