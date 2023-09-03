// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int ans;
  int n;
  vector<vector<int>> stat;

  void Check(int l, int r) {
    if (stat[l].empty() || stat[r].empty()) {
      return;
    }

    int rightPos = stat[r][0];

    for (int i = 0; i < stat[l].size(); i++) {
      if (stat[l][i] < rightPos) {  // 找到一个答案
        ans = min(ans, n - stat[l][i] - 2);
      }
    }
  }

 public:
  int minimumOperations(string num) {
    n = num.size();
    stat.resize(10);
    for (int i = n - 1; i >= 0; i--) {
      stat[num[i] - '0'].push_back(i);
    }

    ans = n;

    if (stat[0].size() >= 1) {  // 0
      ans = min(ans, n - 1);
    }
    Check(0, 0);
    Check(2, 5);
    Check(5, 0);
    Check(7, 5);

    return ans;
  }
};