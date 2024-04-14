// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool Check(int v, char a, char b) {
    if (a != '?' && v / 10 != a - '0') return false;
    if (b != '?' && v % 10 != b - '0') return false;
    return true;
  };
  // 最早的时间为 00:00，最晚的时间为 11:59。
  string findLatestTime(string s) {
    for (int i = 11; i >= 0; i--) {
      if (Check(i, s[0], s[1])) {
        s[0] = '0' + (i / 10);
        s[1] = '0' + (i % 10);
        break;
      }
    }
    for (int i = 59; i >= 0; i--) {
      if (Check(i, s[3], s[4])) {
        s[3] = '0' + (i / 10);
        s[4] = '0' + (i % 10);
        break;
      }
    }
    return s;
  }
};