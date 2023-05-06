// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  map<pair<int, int>, int> h;
  map<int, pair<int, int>> H;
  void Add(int x, int y) {
    pair<int, int> k = {x, y};
    if (h.count(k) == 0) {
      int v = h.size();
      h.insert({k, v});
      H.insert({v, k});
    }
  }
  int Get(int x, int y) {
    pair<int, int> k = {x, y};
    return h[k];
  }

  int n;
  vector<vector<int>> g;

  int Dis(int i, int j) {
    auto [x0, y0] = H[i];
    auto [x1, y1] = H[j];
    return abs(x0 - x1) + abs(y0 - y1);
  }

 public:
  int minimumCost(vector<int>& start, vector<int>& target,
                  vector<vector<int>>& specialRoads) {
    Add(start[0], start[1]);
    Add(target[0], target[1]);
    for (auto& v : specialRoads) {
      int x0 = v[0], y0 = v[1];
      int x1 = v[2], y1 = v[3];
      Add(x0, y0);
      Add(x1, y1);
    }

    n = h.size();
    g.resize(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = Dis(i, j);
      }
    }

    for (auto& v : specialRoads) {
      int x0 = v[0], y0 = v[1];
      int x1 = v[2], y1 = v[3];
      int d = v[4];
      int i = Get(x0, y0);
      int j = Get(x1, y1);
      g[i][j] = min(g[i][j], d);
    }

    vector<int> dis(n + 1, INT_MAX);
    vector<bool> flag(n, false);

    int s = Get(start[0], start[1]);
    int t = Get(target[0], target[1]);

    dis[s] = 0;
    while (!flag[t]) {
      int now = n;  // 找到未处理列表中，举例源点最近的节点
      for (int i = 0; i < n; i++) {
        if (flag[i]) continue;
        if (dis[now] > dis[i]) {
          now = i;
        }
      }

      flag[now] = true;
      for (int i = 0; i < n; i++) {
        dis[i] = min(dis[i], dis[now] + g[now][i]);
      }
    }
    return dis[t];
  }
};