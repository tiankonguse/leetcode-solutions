// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int minimumMoves(string& s) {
    int ans = 0;
    int n = s.length();
    int i = 0;
    while (i < n) {
      if (i < n && s[i] != 'X') {
        i++;
        continue;
      }
      ans++;
      i += 3;
    }
    return ans;
  }
};