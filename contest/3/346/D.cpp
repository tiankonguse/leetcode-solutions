// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<pair<int, int>>> g;
  vector<int> flag;
  // {sum, zero, pre}
  vector<vector<int>> edges;
  int n;
  int S, D, T;
  vector<vector<int>> empty;
    

  void Solver1(vector<tuple<ll, int, int>>& minPath) {
    flag.clear();
    flag.resize(n, 0);
    minPath.clear();
    minPath.resize(n, {-1, 0, -1});

    int findNode = 0;
    minPath[S] = {0, 0, -1};
      
    while (findNode < n) {
      int a = -1;  // 当前最短的节点
      for (int i = 0; i < n; i++) {
        if (flag[i]) continue;
        if (get<0>(minPath[i]) == -1) continue;
        if (a == -1 || get<0>(minPath[a]) > get<0>(minPath[i])) {
          a = i;
        }
      }
      flag[a] = 1;
      findNode++;

      auto [aw, ae, aPre] = minPath[a];
      for (auto [b, e] : g[a]) {
        if (flag[b]) continue;
        ll w = edges[e][2];

        auto& [bw, be, bpre] = minPath[b];
        if (w == -1) {
          if (bw == -1 || (bw > aw + 1) || (bw == aw + 1 && be < ae + 1)) {
            minPath[b] = {aw + 1, ae + 1, e};
          } else {
            // do nothing
          }
        } else {
          if (bw == -1 || (bw > aw + w) || (bw == aw + w && be < ae)) {
            minPath[b] = {aw + w, ae, e};
          } else {
            // do nothing
          }
        }
      }
    }
  }

  void Solver(vector<tuple<ll, int, int>>& minPath) {
    flag.clear();
    flag.resize(n, 0);
    minPath.clear();
    minPath.resize(n, {-1, 0, -1});

    int findNode = 0;
    minPath[S] = {0, 0, -1};
      
    while (findNode < n) {
      int a = -1;  // 当前最短的节点
      for (int i = 0; i < n; i++) {
        if (flag[i]) continue;
        if (get<0>(minPath[i]) == -1) continue;
        if (a == -1 || get<0>(minPath[a]) > get<0>(minPath[i])) {
          a = i;
        }
      }
      flag[a] = 1;
      findNode++;

      auto [aw, ae, aPre] = minPath[a];
      for (auto [b, e] : g[a]) {
        if (flag[b]) continue;
        ll w = edges[e][2];

        auto& [bw, be, bpre] = minPath[b];
        if (w == -1) {
          if (bw == -1 || (bw > aw + 1) || (bw == aw + 1 && be < ae + 1)) {
            minPath[b] = {aw + 1, ae + 1, e};
          } else {
            // do nothing
          }
        } else {
          if (bw == -1 || (bw > aw + w) || (bw == aw + w && be < ae)) {
            minPath[b] = {aw + w, ae, e};
          } else {
            // do nothing
          }
        }
      }
    }
  }

 public:
  vector<vector<int>> modifiedGraphEdges(const int n_,
                                         vector<vector<int>>& edges_,
                                         const int S_, const int D_,
                                         const int T_) {
    n = n_;
    S = S_, D = D_, T = T_;
    edges.swap(edges_);
      
    g.resize(n);
    for (int i = 0; i < edges.size(); i++) {
      auto& v = edges[i];
      int a = v[0], b = v[1];
      g[a].push_back({b, i});
      g[b].push_back({a, i});
    }

    vector<tuple<ll, int, int>> minPath;
    Solver1(minPath);


    auto& [dw, de, dpre] = minPath[D];
    
    if (dw > T) return empty;
    if (dw < T && de == 0) return empty;
      printf("next\n");

    // 逆向设置答案
    int p = D;
    bool flagLeft = false;
    while (p != S) {
      auto& [pw, pe, e] = minPath[p];
      int a = edges[e][0], b = edges[e][1], w = edges[e][2];
      if (edges[e][2] == -1) {
        if (!flagLeft) {
          edges[e][2] = T - dw + 1;
          flagLeft = true;
        } else {
          edges[e][2] = 1;
        }
      }

      if (a == p) {
        p = b;
      } else {
        p = a;
      }
    }

    for (auto& v : edges) {
      if (v[2] == -1) {
        v[2] = T + 1;
      }
    }

    // Solver();
    // if (get<0>(minPath[D]) < T) return empty;

    return edges;
  }
};