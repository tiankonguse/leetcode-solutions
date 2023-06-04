// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  int maxIncreasingCells(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat.front().size();

    min_queue<tuple<int, int, int>> que;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        que.push({mat[i][j], i, j});
      }
    }

    vector<pair<int, int>> irow0(n, {INT_MIN, 0});
    vector<pair<int, int>> jrow0(m, {INT_MIN, 0});
    vector<pair<int, int>> irow1(n, {INT_MIN, 0});
    vector<pair<int, int>> jrow1(m, {INT_MIN, 0});
    int ans = 1;
    int pre = INT_MIN;
    vector<pair<int, int>> buf;
    buf.reserve(n * m);

    while (!que.empty()) {
      const auto [v, i, j] = que.top();
      que.pop();

      if (v != pre) {
        pre = v;
        while (!buf.empty()) {
          auto [x, y] = buf.back();
          buf.pop_back();
          if (irow0[x].second < irow1[x].second) {
            irow0[x] = irow1[x];
          }
          if (jrow0[y].second < jrow1[y].second) {
            jrow0[y] = jrow1[y];
          }
        }
      }
      buf.push_back({i, j});

      int v_ans = 1;
      if (v > irow0[i].first) {
        v_ans = max(v_ans, irow0[i].second + 1);
      }
      if (v > jrow0[j].first) {
        v_ans = max(v_ans, jrow0[j].second + 1);
      }

      if (v_ans > irow1[i].second) {
        irow1[i] = {v, v_ans};
      }
      if (v_ans > jrow1[j].second) {
        jrow1[j] = {v, v_ans};
      }
      ans = max(ans, v_ans);
    }

    return ans;
  }
};