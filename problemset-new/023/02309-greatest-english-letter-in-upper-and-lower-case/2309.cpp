// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  string greatestLetter(string s) {
    set<char> m;
    char A = 'A';
    char ans = A - 1;
    for (auto c : s) {
      m.insert(c);
      if (c >= 'a' && c <= 'z') {
        char C = c - 'a' + 'A';
        if (m.count(c) && m.count(C)) {
          ans = max(ans, C);
        }
      } else {
        char C = c - 'A' + 'a';
        if (m.count(c) && m.count(C)) {
          ans = max(ans, c);
        }
      }
    }
    if (ans >= A) {
      return {ans};
    } else {
      return "";
    }
  }
};