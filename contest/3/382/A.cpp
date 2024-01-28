// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countKeyChanges(const string& s) {
    char pre = ' ';
    int ans = -1;
    for (auto c : s) {
      if (c >= 'A' && c <= 'Z') {
        c = c - 'A' + 'a';
      }
      if (c != pre) {
        ans++;
      }
      pre = c;
    }
    return ans;
  }
};