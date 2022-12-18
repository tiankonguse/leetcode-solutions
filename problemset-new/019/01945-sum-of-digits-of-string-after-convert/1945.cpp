// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  int Cal(int v) {
    int ans = 0;
    while (v) {
      ans = ans + (v % 10);
      v /= 10;
    }
    return ans;
  }

 public:
  int getLucky(string& s, int k) {
    int ans = 0;
    for (auto c : s) {
      int v = c - 'a' + 1;
      ans += Cal(v);
    }

    k--;
    while (k--) {
      ans = Cal(ans);
    }
    return ans;
  }
};