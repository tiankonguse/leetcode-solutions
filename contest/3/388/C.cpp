// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<string> shortestSubstrings(vector<string>& arr) {
    int n = arr.size();
    vector<set<string>> sub(n);
    unordered_map<string, int> h;
    string tmp;
    for (int i = 0; i < n; i++) {
      const string& s = arr[i];
      int m = s.size();
      for (int j = 0; j < m; j++) {
        tmp.clear();
        for (int k = j; k < m; k++) {
          tmp.push_back(s[k]);
          sub[i].insert(tmp);
        }
      }

      for (auto& s : sub[i]) {
        h[s]++;
      }
    }

    vector<string> ans(n);
    for (int i = 0; i < n; i++) {
      for (auto& s : sub[i]) {
        if (h[s] == 1) {
          if (ans[i].size() == 0) {
            ans[i] = s;
          } else if (ans[i].size() > s.size()) {
            ans[i] = s;
          } else if (ans[i].size() == s.size() && ans[i] > s) {
            ans[i] = s;
          }
        }
      }
    }
    return ans;
  }
};