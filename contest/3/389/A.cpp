// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool Check(const char a, const char b, const string& s) {
    int n = s.size();
    for (int i = 0; i + 1 < n; i++) {
      if (s[i] == a && s[i + 1] == b) {
        return true;
      }
    }
    return false;
  }

 public:
  bool isSubstringPresent(const string& s) {
    int n = s.size();
    for (int i = 1; i < n; i++) {
      if (Check(s[i], s[i - 1], s)) {
        return true;
      }
    }
    return false;
  }
};