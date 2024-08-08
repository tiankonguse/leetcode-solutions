// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> shortestDistanceAfterQueries(const int n,
                                           vector<vector<int>>& queries) {
    vector<vector<int>> g(n);
    for (int i = n - 2; i >= 0; i--) {
      g[i].push_back(i + 1);
    }
    vector<int> ans;
    ans.reserve(queries.size());

    int index = 0;
    vector<int> flag(n, index);
    auto solver = [&n, &index, &g, &flag]() -> int {
      index++;
      queue<pair<int, int>> que;
      que.push({0, 0});
      flag[0] = index;

      while (!que.empty()) {
        auto [from, cost] = que.front();
        que.pop();
        int newCost = cost + 1;
        for (auto to : g[from]) {
          if (flag[to] == index) continue;  // 已经扫描过了
          if (to == n - 1) {
            return newCost;
          }

          flag[to] = index;
          que.push({to, newCost});
        }
      }
      return 1;
    };

    for (auto& q : queries) {
      g[q[0]].push_back(q[1]);
      ans.push_back(solver());
    }
    return ans;
  }
};