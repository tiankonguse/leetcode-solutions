// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSpecialChars(string word) {
    set<char> h(word.begin(), word.end());
    int ans = 0;
    for (char c = 'a'; c <= 'z'; c++) {
      char C = c - 'a' + 'A';
      if (h.count(c) && h.count(C)) {
        ans++;
      }
    }
    return ans;
  }
};