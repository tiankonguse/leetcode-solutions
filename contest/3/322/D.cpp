#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

class Solution {
  vector<vector<int>> groups;
  vector<vector<int>> g;
  vector<int> vis;
  int N;
  vector<int> now, next, lev;
  int Solver(int s, int index) {
    int n = groups[index].size();
    now.clear();
    next.clear();
    lev.clear();
    lev.resize(N, -1);

    int num = 1;
    now.push_back(s);
    lev[s] = 1;

    int nowLev = 0;
    while (!now.empty()) {
      nowLev = nowLev + 1;
      int preLev = nowLev - 1;
      int nextLev = nowLev + 1;
      for (auto a : now) {
        for (auto b : g[a]) {
          if (lev[b] == -1) {
            num++;
            lev[b] = nextLev;
            next.push_back(b);
          } else {
            if (lev[b] != preLev && lev[b] != nextLev) {
              // printf("ret=-1 index=%d n=%d b=%d levb=%d nowLev=%d\n", index, n,
              //        b, lev[b], nowLev);
              return -1;
            }
          }
        }
      }

      next.swap(now);
      next.clear();
    }

    if (num != n) {
      // printf("ret=-1 index=%d n=%d num=%d\n", index, n, num);
      return -1;
    }
    return nowLev;
  }

  void Dfs(int s, int index) {
    if (vis[s]) return;
    vis[s] = 1;
    groups[index].push_back(s);
    for (auto t : g[s]) {
      Dfs(t, index);
    }
  }

  int SolverGroup(int index) {
    int ans = -1;
    for (auto s : groups[index]) {
      int ret = Solver(s, index);
      if (ret == -1) continue;
      if (ans == -1) {
        ans = ret;
      } else {
        ans = max(ans, ret);
      }
    }
    return ans;
  }

 public:
  int magnificentSets(int n, vector<vector<int>>& edges) {
    N = n;
    g.resize(n);
    for (auto& v : edges) {
      int a = v[0] - 1, b = v[1] - 1;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    now.reserve(n);
    next.reserve(n);
    lev.reserve(n);

    groups.resize(n);
    vis.resize(n, 0);
    int groupIndex = 0;
    for (int i = 0; i < n; i++) {
      if (vis[i] == 0) {
        Dfs(i, groupIndex);
        // printf("groupIndex = %d size=%d\n", groupIndex,
        //        groups[groupIndex].size());
        groupIndex++;
      }
    }

    // printf("group = %d\n", groupIndex);

    int ans = 0;
    for (int index = 0; index < groupIndex; index++) {
      if (groups[groupIndex].size() == 1) {
        ans++;
        continue;
      }
      int ret = SolverGroup(index);
      if (ret == -1) {
        // printf("groupIndex = %d, ret = %d\n", index, ret);
        return -1;
      }
      ans += ret;
    }
    return ans;
  }
};