// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll countSubstrings(const string& s, char c) {
    int n = s.size();
    ll num = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i - 1] == c) {
        num++;
      }
    }
    return num + num * (num - 1)/2;
  }
};