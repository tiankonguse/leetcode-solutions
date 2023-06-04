// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string removeTrailingZeros(string num) {
    while (num.size() > 1 && num.back() == '0') {
      num.pop_back();
    }
    return num;
  }
};