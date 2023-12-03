// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countCompleteSubstrings(const string& word, int k) {
    int ans = 0;
    int n = word.size();
    vector<vector<int>> stat(n + 1, vector<int>(26, 0));
    for (int i = 1; i <= n; i++) {
      const int c = word[i - 1] - 'a';
      stat[i] = stat[i - 1];
      stat[i][c]++;
    }
    set<int> limit;
    for (int i = 1; i < n; i++) {
      int a = word[i - 1] - 'a';
      int b = word[i] - 'a';
      if (a > b) {
        swap(a, b);
      }
      if (a + 2 < b) {
        limit.insert(i);
      }
    }

    auto Check = [&stat, &k](const int l, const int r) -> bool {  //[l, r]
      for (int c = 0; c < 26; c++) {
        const int dis = stat[r][c] - stat[l - 1][c];
        if (dis == 0) continue;
        if (dis != k) return false;
      }
      return true;
    };

    for (int i = 1; i <= n; i++) {
      for (int count = 1; count <= 26; count++) {
        const int l = i, r = i + count * k - 1;  //[l, r]
        if (r > n) break;
        auto it = limit.lower_bound(l);
        if (it != limit.end() && *it < r) break;  // 规则2
        const int res = Check(l, r);
        // printf("[%d,%d) count=%d k=%d res=%d s=%s\n", l, r, count, k,
        // res,word.substr(l-1, count * k).c_str());
        if (res) {
          ans++;
        }
      }
    }
    return ans;
  }
};