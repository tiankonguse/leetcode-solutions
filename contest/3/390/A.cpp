// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumLengthSubstring(const string& s) {
    unordered_map<char, int> h;
    int ans = 1;
    int l = 0, r = 0;  // [l, r)
    int n = s.size();

    while (r < n) {
      while (r < n && h[s[r]] + 1 <= 2) {
        h[s[r]]++;
        r++;
      }
      ans = max(ans, r - l);

      if (r == n) break;

      char c = s[r];
      while (s[l] != c) {
        h[s[l]]--;
        l++;
      }
      h[s[l]]--;
      l++;
    }

    return ans;
  }
};