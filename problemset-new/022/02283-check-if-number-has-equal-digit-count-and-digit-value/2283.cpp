// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool digitCount(string num) {
    map<char, int> m;
    for (auto v : num) {
      m[v-'0']++;
    }

    for (int i = 0; i < num.size(); i++) {
      if (m[i] != (num[i] - '0')) {
          return false;
      }
    }
    return true;
  }
};