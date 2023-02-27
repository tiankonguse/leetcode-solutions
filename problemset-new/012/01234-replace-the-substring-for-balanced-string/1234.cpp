// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  string C = "QWER";
  bool Less(unordered_map<char, int>& l, unordered_map<char, int>& r) {
    for (auto c : C) {
      if (l[c] < r[c]) return true;
    }
    return false;
  }

 public:
  int balancedString(const string& s) {
    int n = s.length();
    int n4 = n / C.size();
    unordered_map<char, int> h;
    unordered_map<char, int> minVal;
    unordered_map<char, int> now;

    for (auto c : s) {
      h[c]++;
    }

    for (auto c : C) {
      minVal[c] = max(h[c] - n4, 0);
      now[c] = 0;
    }

    if (!Less(now, minVal)) return 0;

    int ans = n;
    int l = 0, r = 0;  //[l, r)
    while (l < n) {
      while (r < n && Less(now, minVal)) {
        now[s[r]]++;
        r++;
      }
      if (Less(now, minVal)) break;
      ans = min(ans, r - l);

      if (l < r) {
        now[s[l]]--;
        l++;
      }
    }
    return ans;
  }
};