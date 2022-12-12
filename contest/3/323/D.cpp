// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  min_queue<tuple<int, int, int>> que;
  int n, m;

  vector<vector<int>> grid;
  int point_num = 0;
  int Query(const int v) {
    while (!que.empty()) {
      auto [V, X, Y] = que.top();
      if (V >= v) break;
      que.pop();

      point_num++;

      for (int i = 0; i < 4; i++) {
        int x = X + dir4[i][0];
        int y = Y + dir4[i][1];
        if (x < 0 || x >= n || y < 0 || y >= m) continue;
        if (grid[x][y] == -1) continue;

        que.push({grid[x][y], x, y});
        grid[x][y] = -1;
      }
    }
    return point_num;
  }

 public:
  vector<int> maxPoints(vector<vector<int>>& grid_, vector<int>& queries) {
    grid.swap(grid_);
    n = grid.size();
    m = grid.front().size();

    vector<pair<int, int>> qs(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      qs.push_back({queries[i], i});
    }
    sort(qs.begin(), qs.end());

    que.push({grid[0][0], 0, 0});
    grid[0][0] = -1;

    vector<int> ans(qs.size(), 0);
    for (auto [v, i] : qs) {
      ans[i] = Query(v);
    }
    return ans;
  }
};