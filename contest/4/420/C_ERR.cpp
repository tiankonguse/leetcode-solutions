// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

class Solution {
  vector<vector<ll>> g;

 public:
  int minOperations(vector<int>& nums) {
    ll n = nums.size();
    g.resize(n);
    for (int i = 0; i < n; i++) {
      const ll V = nums[i];
      auto& result = g[i];
      for (ll j = 2; j * j <= V; j++) {
        if (V % j == 0) {
          result.push_back(j);
          if (V / j != j) {
            result.push_back(V / j);
          }
        }
      }
      result.push_back(V);
      sort(result.begin(), result.end());
      myprintf("V=%lld: ", V);
      for (auto v : result) {
        myprintf(" %lld", v);
      }
      myprintf("\n");
    }

    vector<ll> pre;
    vector<ll> now;
    pre.resize(g[0].size(), 1);
    pre.back() = 0;  // 最后一个不需要修改，之前的都需要修改
    for (ll i = 1; i < n; i++) {
      const auto preG = g[i - 1];
      now.clear();
      now.resize(g[i].size(), -1);
      myprintf("i=%lld:\n", i);
      for (ll j = 0; j < g[i].size(); j++) {
        const ll v = g[i][j];
        ll offset = upper_bound(preG.begin(), preG.end(), v) - preG.begin() - 1;
        myprintf("j=%lld offset=%lld\n", j, offset);
        if (offset == -1 || pre[offset] == -1) {  // 太小了，不存在答案
          now[j] = -1;
          continue;
        }
        now[j] = pre[offset];
        if (j + 1 < g[i].size()) {  // 最后一个不需要加1
          now[j]++;
        }
      }
      pre.swap(now);
    }

    return pre.back();
  }
};
