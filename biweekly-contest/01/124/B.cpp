// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string lastNonEmptyString(const string& s) {
    unordered_map<char, int> h;
    int num = 0;
    for (auto c : s) {
      h[c]++;
      num = max(num, h[c]);
    }

    string ans;
    for (int i = s.length() - 1; i >= 0; i--) {
      char c = s[i];
      if (h[c] == num) {
        ans.push_back(c);
        h[c]--;
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};