// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string finalString(string s) {
    string ans;
    for (auto c : s) {
      if (c == 'i') {
        std::reverse(ans.begin(), ans.end());
      } else {
        ans.push_back(c);
      }
    }
    return ans;
  }
};
