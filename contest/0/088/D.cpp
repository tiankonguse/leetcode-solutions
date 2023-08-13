// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
  vector<vector<int>> next;
  vector<int> ans;
  void dfsUpdate(int x, vector<int>& quiet) {
    for (int i = 0; i < next[x].size(); i++) {
      int y = next[x][i];
      if (quiet[ans[y]] > quiet[ans[x]]) {
        ans[y] = ans[x];
        dfsUpdate(y, quiet);
      }
    }
  }
  // person x 比 person y 更有钱
  void addRicher(int x, int y, vector<int>& quiet) {
    next[x].push_back(y);
    if (quiet[ans[y]] > quiet[ans[x]]) {
      ans[y] = ans[x];
      dfsUpdate(y, quiet);
    }
  }

 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    next.clear();
    ans.clear();
    for (int i = 0; i < quiet.size(); i++) {
      ans.push_back(i);
      next.push_back(vector<int>());
    }

    for (int i = 0; i < richer.size(); i++) {
      addRicher(richer[i][0], richer[i][1], quiet);
    }
    return ans;
  }
};