// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<pair<int, int>>> tree;
  unordered_map<int, ll> base;
  // 没有奇数或者只有一个奇数，形成回文数
  ll Dfs(int now, int mask) {
    ll ans = 0;
    for (auto [child, path] : tree[now]) {
      int maskNew = mask ^ (1 << path);
      ans += base[maskNew];
      for (int i = 0; i < 26; i++) {
        ans += base[maskNew ^ (1 << i)];
      }
      base[maskNew]++;
      ans += Dfs(child, maskNew);
    }

    // printf("now=%d ans=%lld\n", now, ans);
    return ans;
  }

 public:
  ll countPalindromePaths(vector<int>& parent, const string& s) {
    int n = parent.size();
    tree.resize(n);
    for (int i = 1; i < n; i++) {
      int p = parent[i];
      tree[p].push_back({i, int(s[i] - 'a')});
    }

    base[0] = 1;
    return Dfs(0, 0);
  }
};