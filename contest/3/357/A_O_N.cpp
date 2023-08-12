// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string finalString(string s) {
    string left, right;
    std::reverse(s.begin(), s.end());
    bool flag = false;
    for (auto c : s) {
      if (c == 'i') {
        flag = !flag;
      } else {
        if (flag) {
          left.push_back(c);
        } else {
          right.push_back(c);
        }
      }
    }
    std::reverse(right.begin(), right.end());
    return left + right;
  }
};
