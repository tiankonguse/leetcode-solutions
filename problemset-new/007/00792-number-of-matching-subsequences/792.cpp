#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numMatchingSubseq(const string& s, vector<string>& words) {
    int n = s.size();
    vector<vector<int>> next(n + 1, vector<int>(26, -1));

    vector<int> pos(26, -1);
    for (int i = n; i > 0; i--) {
      pos[s[i - 1] - 'a'] = i;
      next[i - 1] = pos;
    }

    int ans = 0;
    for (auto& str : words) {
      int p = 0;
      for (auto c : str) {
        p = next[p][c - 'a'];
        if (p == -1) {
          break;
        }
      }
      if (p != -1) {
        ans++;
      }
    }
    return ans;
  }
};