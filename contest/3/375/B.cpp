// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
class Solution {
 public:
  vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
    vector<int> ans;
    ans.reserve(variables.size());
    for (int i = 0; i < variables.size(); i++) {
      const auto& v = variables[i];
      ll a = v[0];
      ll b = v[1];
      ll c = v[2];
      ll m = v[3];
      if (qpow(qpow(a, b, 10), c, m) == target) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};