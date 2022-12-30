// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumLength(string s) {
    int l = 0, r = s.length() - 1;  // [l, r]

    while (l <= r && s[l] == s[r]) {
      const char c = s[l];
      while (l <= r && c == s[l]) l++;
      while (l <= r && c == s[r]) r--;
    }
    return r - l + 1;
  }
};