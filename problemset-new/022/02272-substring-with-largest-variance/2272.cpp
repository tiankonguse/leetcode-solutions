#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int largestVariance(string s) {
    int n = s.size();
    int ans = 0;
    for (char a = 'a'; a <= 'z'; a++) {
      for (char b = 'a'; b <= 'z'; b++) {
        if (a == b) continue;
        int preAB = -1;
        int preBB = n * -10;

        for (auto c : s) {
          if (c == a) {
            preAB = max(preAB, 0) + 1;
            preBB = preBB + 1;
          } else if (c == b) {
            preBB = max(max(-1, preBB - 1), preAB - 1);
            preAB = max(preAB, 0) - 1;
          }
          ans = max(ans, preBB);
        }
      }
    }
    return ans;
  }
};