// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minLength(string s) {
    string ans;
    for (auto c : s) {
      if (!ans.empty()) {
        if (ans.back() == 'A' && c == 'B') {
          ans.pop_back();
          continue;
        } else if (ans.back() == 'C' && c == 'D') {
          ans.pop_back();
          continue;
        }
      }

      ans.push_back(c);
    }
    return ans.size();
  }
};