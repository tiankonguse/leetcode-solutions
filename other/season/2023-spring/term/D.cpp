// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  int n;

  void Dfs(int now, string& preAns, int& len, int pre = -1) {
    int childNum = g[now].size();
    vector<pair<string, int>> childs;
    childs.reserve(childNum);

    for (auto child : g[now]) {
      if (child == pre) continue;
      childs.push_back({"", 0});

      auto& [childAns, childLen] = childs.back();
      childAns.push_back('0');
      Dfs(child, childAns, childLen, now);
      childAns.push_back('1');
      childLen++;
    }
    sort(childs.begin(), childs.end());

    for (auto& [childAns, childLen] : childs) {
      preAns.append(childAns);
      len = childLen;
    }
  }

 public:
  string evolutionaryRecord(vector<int>& parents) {
    n = parents.size();
    g.resize(n);
    for (int i = 1; i < n; i++) {
      int v = parents[i];
      g[v].push_back(i);
    }
    string ans;
    int len;
    Dfs(0, ans, len);
    printf("ans=%s len=%d\n", ans.c_str(), len);
    ans.resize(ans.size() - len);
    return ans;
  }
};
