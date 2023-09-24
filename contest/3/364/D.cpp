// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 100010;
const int M = 9696;
bool is[N];
int prm[M];
int K = 0;
int GetPrm() {
  if (K != 0) return K;
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return K = k;
}

class Solution {
  vector<vector<int>> g;
  vector<ll> emptyChild;  // 到根节点的路径中没有质数的路径数（包括根节点）
  vector<ll> prmChild;  // 到根节点的路径中没有质数的路径数（包括根节点）
  ll ans = 0;

  void Dfs(int from, int pre) {
    int fromValue = is[from];

    ll empty = 0;
    ll prm = 0;
    for (auto to : g[from]) {
      if (to == pre) continue;
      Dfs(to, from);
      empty += emptyChild[to];
      prm += prmChild[to];
    }
    // printf("child: from=%d fromValue=%d empty=%lld prm=%lld\n", from, fromValue,
    //        empty, prm);

    if (fromValue == 1) {  // 根节点是素数

      ans += empty;  // 根节点为一个端点

      // printf("add ans: prm root, +%lld\n", empty);
      ll tmp = 0;
      for (auto to : g[from]) {  // 根节点为中间节点
        if (to == pre) continue;
        ll other = empty - emptyChild[to];
        tmp += other * emptyChild[to];
        // printf("add ans: prm mid, %lld * %lld = %lld\n", other, emptyChild[to],
        //        other * emptyChild[to]);
      }
      ans += tmp / 2;
      emptyChild[from] = 0;        // 这条路径没有空节点
      prmChild[from] = empty + 1;  // 素数下的节点个数
      // printf("from=%d, emptyChild=%lld, prmChild=%lld\n", from,
      //        emptyChild[from], prmChild[from]);
    } else {  // 根节点不是素数
      empty++;
      for (auto to : g[from]) {
        if (to == pre) continue;
        ll other = empty - emptyChild[to];
        ans += other * prmChild[to];

        // printf("add ans: from empty, %lld * %lld = %lld\n", other, prmChild[to],
        //        other * prmChild[to]);
      }
      emptyChild[from] = empty;
      prmChild[from] = prm;
      // printf("from=%d, emptyChild=%lld, prmChild=%lld\n", from,
      //        emptyChild[from], prmChild[from]);
    }
  }

 public:
  ll countPaths(int n, vector<vector<int>>& edges) {
    GetPrm();
    g.resize(n + 1);
    emptyChild.resize(n + 1, 0);
    prmChild.resize(n + 1, 0);
    for (auto& e : edges) {
      int a = e[0], b = e[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }
    Dfs(1, -1);
    return ans;
  }
};