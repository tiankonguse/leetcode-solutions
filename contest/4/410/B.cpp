// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  int n;
  int ans;
  int Dfs(int a, int p) {
    int flag = 1;  // 0 一个值， 1 不同
    int num = -1;
    int sum = 1;
    for (auto b : g[a]) {
      if (p == b) continue;
      int v = Dfs(b, a);
      sum += v;
      if (num == -1) {
        num = v;
      } else if (num != v) {
        flag = 0;
      }
    }

    if (flag) {
      ans++;
    }
    return sum;
  }

 public:
  int countGoodNodes(vector<vector<int>>& edges) {
    n = edges.size() + 1;
    g.resize(n);
    for (auto& e : edges) {
      int a = e[0];
      int b = e[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }
    ans = 0;
    Dfs(0, -1);
    return ans;
  }
};