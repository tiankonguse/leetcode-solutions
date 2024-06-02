// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string clearStars(string s) {
    int n = s.length();
    map<char, vector<int>> h;
    for (int i = 0; i < n; i++) {
      char& c = s[i];
      if (c != '*') {
        h[c].push_back(i);
        continue;
      }

      c = ' ';
      auto it = h.begin();
      s[it->second.back()] = ' ';
      it->second.pop_back();
      if (it->second.size() == 0) {
        h.erase(it);
      }
    }

    string ans;
    ans.reserve(s.size());
    for (auto c : s) {
      if (c != ' ') {
        ans.push_back(c);
      }
    }
    return ans;
  }
};