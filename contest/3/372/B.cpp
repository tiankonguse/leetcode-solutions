// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minimumSteps(string s) {
    ll ans = 0;
    ll black = 0;
    for (auto c : s) {
      if (c == '1') {
        black++;
      } else {
        ans += black;
      }
    }
    return ans;
  }
};