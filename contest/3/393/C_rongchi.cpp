// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
// str[n].count;
// Str[n].prim[];
// LL myrongchi(int index, int a, int n) {
//   LL r = 0, t;
//   for (int i = index; i < str[n].count; i++) {
//     t = a / str[n].prim[i];
//     r += t - myrongchi(i + 1, t, n);
//   }
//   return r;
// }
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}
ll Lcd(ll x, ll y) { return x / Gcd(x, y) * y; }
class Solution {
  vector<int> coins;
  int n;
  ll rongchi(int index, ll sum, ll pre = 1) {
    ll ans = 0;
    for (int i = index; i < n; i++) {
      ll tmp = Lcd(coins[i], pre);
      ans += sum / tmp - rongchi(i + 1, sum, tmp);
    }
    return ans;
  }

 public:
  long long findKthSmallest(vector<int>& coins_, ll k) {
    coins.swap(coins_);
    n = coins.size();
    sort(coins.begin(), coins.end());
    ll l = 1;
    ll r = coins.front() * k + 1;  //[l, r]
    while (l < r) {
      ll mid = (l + r) / 2;
      int K = rongchi(0, mid);
      if (K < k) {
        l = mid + 1;  // mid 不够，肯定在右边
      } else if (K > k) {
        r = mid - 1;  // 超了，肯定在左边
      } else {
        r = mid;
      }
    }
    return r;
  }
};