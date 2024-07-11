// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<string> ans;
  int n;
  string buf;
  void Dfs(int p) {
    if (p == n) {
      ans.push_back(buf);
      return;
    }
    for (int i = 0; i < 2; i++) {
      char v = '0' + i;
      if (buf.size() > 0 && buf.back() == v && i == 0) {
        continue;
      }
      buf.push_back(v);
      Dfs(p + 1);
      buf.pop_back();
    }
  }

 public:
  vector<string> validStrings(int n_) {
    n = n_;
    ans.reserve(1 << n);
    buf.reserve(n);
    Dfs(0);
    return ans;
  }
};