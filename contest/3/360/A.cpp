// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int furthestDistanceFromOrigin(string moves) {
    set<int> h;
    h.insert(0);

    for (auto c : moves) {
      set<int> tmp;
      for (auto v : h) {
        if (c == 'L' || c == '_') {
          tmp.insert(v - 1);
        }
        if (c == 'R' || c == '_') {
          tmp.insert(v + 1);
        }
      }
      h.swap(tmp);
    }
    int ans = 0;
    for (auto v : h) {
      ans = max(ans, abs(v));
    }
    return ans;
  }
};