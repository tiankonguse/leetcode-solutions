// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> tree;
  vector<pair<int, int>> childs;
  vector<int> ans;

  void DfsRoot(int root, int pre) {
    auto& [rootNum, rootSum] = childs[root];
    rootNum++;  // 根节点
    for (auto c : tree[root]) {
      if (c == pre) continue;
      DfsRoot(c, root);
      rootNum += childs[c].first;
      rootSum += childs[c].second + childs[c].first;
    }
  }
  void DfsAns(int root, int pre, int preNum = 0, int preSum = 0) {
    auto [rootNum, rootSum] = childs[root];

    rootNum += preNum;
    rootSum += preSum + preNum;
    ans[root] = rootSum;

    for (auto c : tree[root]) {
      if (c == pre) continue;
      auto& [childNum, childSum] = childs[c];
      DfsAns(c, root, rootNum - childNum, rootSum - (childSum + childNum));
    }
  }

 public:
  vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    tree.resize(n);
    for (auto& e : edges) {
      int a = e[0], b = e[1];
      tree[a].push_back(b);
      tree[b].push_back(a);
    }

    childs.resize(n);
    DfsRoot(0, -1);

    ans.resize(n, 0);
    DfsAns(0, -1);
    return ans;
  }
};
