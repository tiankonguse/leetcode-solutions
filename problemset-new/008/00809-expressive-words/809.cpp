#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  void Trans(const string& s, vector<pair<char, int>>& base) {
    base.clear();
    base.push_back({s.front(), 0});
    for (auto c : s) {
      if (c == base.back().first) {
        base.back().second++;
      } else {
        base.push_back({c, 1});
      }
    }
  }
  vector<pair<char, int>> base;
  vector<pair<char, int>> tmp;
  bool Check() {
    if (tmp.size() != base.size()) {
      return false;
    }

    for (int i = 0; i < base.size(); i++) {
      auto [v1, n1] = base[i];
      auto [v2, n2] = tmp[i];
      if (v1 != v2) return false;
      if (n1 < n2) return false;
      if (n1 == n2) continue;
      if (n1 < 3) return false;
    }
    return true;
  }

 public:
  int expressiveWords(const string& s, vector<string>& words) {
    Trans(s, base);
    int ans = 0;
    for (auto& word : words) {
      Trans(word, tmp);
      if (Check()) {
        ans++;
      }
    }
    return ans;
  }
};
