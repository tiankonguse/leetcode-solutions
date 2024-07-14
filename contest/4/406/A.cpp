// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string getSmallestString(string& s) {
    int n = s.size();
    for (int i = 1; i < n; i++) {
      int a = s[i - 1] - '0';
      int b = s[i] - '0';
      if (a % 2 == b % 2 && a > b) {
        swap(s[i - 1], s[i]);
        break;
      }
    }
    return s;
  }
};