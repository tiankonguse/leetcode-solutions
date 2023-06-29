// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}
class Solution {
 public:
  int countBeautifulPairs(const vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    vector<pair<int, int>> left;
    left.reserve(n);
    for (auto v : nums) {
      int last = v % 10;
      while (v >= 10) {
        v = v / 10;
      }
      left.push_back({v, last});
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (Gcd(left[i].first, left[j].second) == 1) {
          ans++;
        }
      }
    }
    return ans;
  }
};