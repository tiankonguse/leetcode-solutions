// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSpecialChars(const string& word) {
    map<char, vector<char>> h;
    for (auto v : word) {
      char key = v;
      if (key >= 'A' && key <= 'Z') {
        key = key - 'A' + 'a';
      }
      auto& list = h[key];
      if (list.empty()) {
        list.push_back(v);
      } else if (list.back() != v && list.size() < 3) {
        if (list.back() != v) {
          list.push_back(v);
        }
      }
    }

    int ans = 0;
    for (char c = 'a'; c <= 'z'; c++) {
      if (!h.count(c)) continue;
      auto& list = h[c];
      int n = list.size();
      char C = c - 'a' + 'A';

      if (list.size() != 2) continue;
      if (list.front() != c) continue;
      if (list.back() != C) continue;
      ans++;
    }
    return ans;
  }
};