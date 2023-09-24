// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string maximumOddBinaryNumber(string s) {
    int one = 0;
    int zero = 0;
    for (auto c : s) {
      if (c == '0') {
        zero++;
      } else {
        one++;
      }
    }
    s.clear();
    one--;
    while (one--) {
      s.push_back('1');
    }
    while (zero--) {
      s.push_back('0');
    }
    s.push_back('1');
    return s;
  }
};