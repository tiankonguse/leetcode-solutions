// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string breakPalindrome(string s) {
    int n = s.length();
    if (n == 1) {
      s.clear();
      return s;
    }

    int mid = n / 2;
    // aabaa(5,2)  | aaaa(4,2)
    for (int i = 0; i < mid; i++) {
      if (s[i] != 'a') {
        s[i] = 'a';
        return s;
      }
    }
    s.back() = 'b';
    return s;
  }
};