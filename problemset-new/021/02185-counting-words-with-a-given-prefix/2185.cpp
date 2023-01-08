#include "base.h"

class Solution {
 public:
  int prefixCount(vector<string>& words, string& pref) {
    int ans = 0;
    int len = pref.length();
    for (auto& s : words) {
      if (s.length() < len) continue;
      if (strncmp(s.c_str(), pref.c_str(), len) == 0) {
        ans++;
      }
    }

    return ans;
  }
};