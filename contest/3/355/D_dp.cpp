// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<pair<int, int>>> tree;

  ll Get(unordered_map<int, ll>& base, int k) {
    if (base.count(k) == 0) return 0;
    return base[k];
  }

  // 没有奇数或者只有一个奇数，形成回文数
  ll Dfs(int now, unordered_map<int, ll>& base) {
    ll ans = 0;
    base[0] = 1;

    // printf("in now=%d\n", now);
    unordered_map<int, ll> h;
    for (auto [child, path] : tree[now]) {
      // printf("in now=%d child=%d\n", now, child);
      ans += Dfs(child, h);  // 计算出儿子子树的答案

      for (auto [mask, num] : h) {
        // 计算追加 path 形成的答案数
        int maskNew = mask ^ (1 << path);
        // if (maskNew == 0 || (maskNew & (maskNew - 1)) == 0) {
        //   ans += num;
        //   printf("now=%d child=%d alone add=%lld\n", now, child, num);
        // }

        // 计算与前面的子树的拼接形成的答案数,分两种情况

        // // 情况1：拼接后是偶数，则前面需要与 maskNew 相同
        int maskEven = maskNew;
        ans += Get(base, maskEven) * num;
        // printf("now=%d child=%d even left=%lld right=%lld add=%lld\n", now,
        //        child, Get(base, maskEven), num, Get(base, maskEven) * num);

        // 情况2：枚举奇数的字符，其余字符为偶数
        for (int i = 0; i < 26; i++) {
          int maskOdd = maskNew ^ (1 << i);  // 奇数位置是 i
          ans += Get(base, maskOdd) * num;
          // printf("now=%d child=%d odd i=%d left=%lld right=%lld add=%lld\n",
          //        now, child, i, Get(base, maskOdd), num,
          //        Get(base, maskOdd) * num);
        }
      }

      for (auto [mask, num] : h) {
        base[mask ^ (1 << path)] += num;
      }
      h.clear();
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

    unordered_map<int, ll> H;
    return Dfs(0, H);
  }
};