#include "base.h"

class Solution {
 public:
  vector<vector<int>> largeGroupPositions(string& s) {
    vector<vector<int>> ans;
    int n = s.length();
    int i = 0;
    char pre = s[0];
    int start = 0;
    while (i < n) {
      start = i;  // first
      pre = s[i];
      while (i < n && pre == s[i]) i++;
      if (i - start >= 3) {
        ans.push_back({start, i - 1});
      }
    }
    return ans;
  }
};