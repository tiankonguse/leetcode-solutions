// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Dis(char a, char b) {
    int aa = a - 'a';
    int bb = b - 'a';
    if (aa > bb) {
      swap(aa, bb);
    }
    int cc = bb - aa;
    return min(cc, 26 - cc);
  }

 public:
  string getSmallestString(string s, int k) {
    int n = s.size();
    for (auto& c : s) {
      if (c == 'a') continue;
      for (char v = 'a'; v < c; v++) {
        int d = Dis(v, c);
        if (d <= k) {
          c = v;
          k -= d;
          break;
        }
      }
    }
    return s;
  }
};