// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll ToMax(string s) {  //
    char firstNotNine = '9';
    for (auto c : s) {
      if (c != '9') {
        firstNotNine = c;
        break;
      }
    }

    for (auto& c : s) {
      if (c == firstNotNine) {
        c = '9';
      }
    }

    return atoll(s.c_str());
  }
  ll ToMin(string s) {  //
    char firstNotZero = '0';
    char to = '0';
    if (s.front() != '1') {
      firstNotZero = s.front();
      to = '1';
    } else {
      for (int i = 1; i < s.size(); i++) {
        if (s[i] != '0' && s[i] != '1') {
          firstNotZero = s[i];
          to = '0';
          break;
        }
      }
    }

    for (auto& c : s) {
      if (c == firstNotZero) {
        c = to;
      }
    }

    return atoll(s.c_str());
  }

 public:
  int maxDiff(int num) {
    string s = to_string(num);
    return ToMax(s) - ToMin(s);
  }
};