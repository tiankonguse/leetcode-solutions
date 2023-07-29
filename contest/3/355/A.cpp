// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
    vector<string> ans;
    for (auto& s : words) {
      string tmp;
      for (auto c : s) {
        if (c == separator) {
          if (!tmp.empty()) {
            ans.push_back(tmp);
          }
          tmp.clear();
        } else {
          tmp.push_back(c);
        }
      }
      if (!tmp.empty()) {
        ans.push_back(tmp);
      }
      tmp.clear();
    }

    return ans;
  }
};