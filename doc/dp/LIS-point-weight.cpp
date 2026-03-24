// 带权的二维坐标最大非递减路径

#include <bits/stdc++.h>

typedef long long ll;
vector<tuple<ll, ll, ll>> points; // (x, y, v)
int n; // 点的个数 points.size()


unordered_map<ll, ll> mp;
vector<ll> ys;
int m; // 离散化后的点的个数 ys.size()
void Discretization() {
  for (int i = 0; i < n; i++) {
    auto [xi, yi, vi] = points[i];
    ys.push_back(yi);
  }
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  m = ys.size();
  for (int i = 0; i < m; i++) {
    mp[ys[i]] = i + 1;
  }
}

// ../struct/fenwick/treeArrayMax.cpp
TreeArrayMax tree; // 树状数组求前缀最大值，也可以使用线段树代替

ll SolverPartialOrder() {
  sort(points.begin(), points.end());
  tree.Init(m);  // [1,m]
  ll ans = 0;
  for (auto [x, y, v] : points) {
    ll offset = mp[y];
    ll newVal = tree.QueryMax(offset) + v;
    tree.SetVal(offset, newVal);
    ans = max(ans, newVal);
  }
  return ans;
}