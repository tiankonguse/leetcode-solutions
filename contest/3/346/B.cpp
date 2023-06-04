// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string makeSmallestPalindrome(string s) {
    int n = s.length();
    int l = 0, r = n - 1;
    while (l < r) {
      if (s[l] == s[r]) continue;
      s[l] = s[r] = min(s[l], s[r]);
      l++;
      r--;
    }
    return s;
  }
};