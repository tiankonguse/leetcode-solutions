// #include <bits/stdc++.h>

#include "base.h"
using namespace std;


typedef long long ll;
class Solution {
  vector<vector<int>> g;
  vector<int> coins;
  int n;

  vector<int> coinDeps;
  vector<int> coinAns0;
  int ans = 0;
  void DfsDep(const int now, const int pre = -1) {
    int maxChildDep = 0;  // 选择当前节点
    int tmpAns = 0;

    for (auto v : g[now]) {
      if (v == pre) continue;
      DfsDep(v, now);
      maxChildDep = max(maxChildDep, coinDeps[v]);
      tmpAns += coinAns0[v];
    }

    // 计算金币的深度
    coinDeps[now] = 0;
    if (coins[now] || maxChildDep > 0) {
      coinDeps[now] = 1 + maxChildDep;
    }

    // 计算根为 0 时，遍历的节点个数
    if (coinDeps[now] <= 2) {
      coinAns0[now] = 0;
    } else {
      coinAns0[now] = 1 + tmpAns;
    }
    if (pre == -1) {
      coinAns0[now] = max(coinAns0[now], 1);  //根节点需要选择
    }
    // printf("root=0  v=%d ans0=%d dep0=%d\n", now, coinAns0[now], coinDeps[now]);
  }
  void DfsAns(const int now, const int pre = -1, const int preDep = 0,
              const int preAns = 0) {
    // 选择当前节点为 根
    int nowAns = max(1, coinAns0[now]) + preAns;
    ans = min(ans, nowAns);

    // 递归求子树的答案
    map<int, int> m;
    int childSum = preAns;
    for (auto v : g[now]) {
      if (v == pre) continue;

      m[coinDeps[v]]++;
      childSum += coinAns0[v];
    }
    // printf("root is %d, nowAns = %d preDep=%d preAns=%d childSum=%d\n", now,
    //        nowAns, preDep, preAns, childSum);

    for (auto v : g[now]) {
      if (v == pre) continue;

      m[coinDeps[v]]--;
      if (m[coinDeps[v]] == 0) {
        m.erase(coinDeps[v]);
      }
      childSum -= coinAns0[v];
    //   printf("root=%d child=%d childSum=%d size=%d\n", now, v, childSum,
    //          m.size());

      int childMaxDep = preDep;
      if (m.size() > 0) {
        childMaxDep = max(childMaxDep, m.rbegin()->first);
      }

      int childDep = 0, childAns = 0;

      // 金币距离大于等于 2，必须选择当前根
      if (childSum > 0 | childMaxDep >= 2) {
        childDep = 3;
        childAns = childSum + 1;
      } else {  // 长度为 0 或 1
        if (childMaxDep == 0) {
          if (coins[now]) {
            childDep = 1;
          } else {
            childDep = 0;
          }
        } else {
          childDep = childMaxDep + 1;
        }
      }

      DfsAns(v, now, childDep, childAns);

      childSum += coinAns0[v];
      m[coinDeps[v]]++;
    }
  }

 public:
  int collectTheCoins(vector<int>& coins_, vector<vector<int>>& edges) {
    coins.swap(coins_);
    n = coins.size();
    g.resize(n);
    for (auto& v : edges) {
      int a = v[0], b = v[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }

    coinDeps.resize(n, 0);
    coinAns0.resize(n, 0);
    DfsDep(0);  // 假设 0 为根，计算各个节点的最远金币深度
    ans = coinAns0[0];
    DfsAns(0);
    return (ans - 1) * 2;
  }
};