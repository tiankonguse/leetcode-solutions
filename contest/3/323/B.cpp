// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  unordered_map<ll, int> m;

  int Dfs(ll a) {
    if (m.count(a) == 0) return 0;
    if (m[a] != -1) return m[a];
    return m[a] = 1 + Dfs(a * a);
  }

 public:
  int longestSquareStreak(vector<int>& nums) {
    for (auto v : nums) {
      m[v] = -1;
    }
    int ans = 0;
    for (auto v : nums) {
      ans = max(ans, Dfs(v));
    }
    if (ans == 1) {
      ans = -1;
    }
    return ans;
  }
};
