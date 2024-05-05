// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isValid(string s) {
    if (s.length() < 3) return false;
    set<char> h = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    int flag = 0;
    for (auto c : s) {
      if (c >= '0' && c <= '9') {
      } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        if (h.count(c)) {
          flag |= 1;
        } else {
          flag |= 2;
        }
      } else {
        return false;
      }
    }
    if (flag != 3) return false;

    return true;
  }
};