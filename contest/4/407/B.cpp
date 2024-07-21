// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool doesAliceWin(const string& s) {
    set<char> h = {'a', 'e', 'i', 'o', 'u'};
    int num = 0;
    for (auto c : s) {
      if (h.count(c)) {
        num++;
      }
    }
    if (num == 0) return false;
    return true;
  }
};