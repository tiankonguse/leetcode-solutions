// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}
ll Lcd(ll x, ll y) { return x * y / Gcd(x, y); }
vector<int> coins; // n 个数字，求第 K 个倍数
int n;
ll rongchi(int index, ll sum, ll pre = 1) {
  if (pre > sum) return 0;
  ll ans = 0;
  for (int i = index; i < n; i++) {
    ll tmp = Lcd(coins[i], pre);
    ans += sum / tmp - rongchi(i + 1, sum, tmp);
  }
  return ans;
}

class Solution {
  void Fix(vector<int>& coins_) {
    sort(coins_.begin(), coins_.end());

    for (auto v : coins_) {
      bool flag = false;
      for (int i = 0; i < coins.size(); i++) {
        int V = coins[i];
        if (v % V == 0) {
          flag = true;
          break;
        }
      }
      if (!flag) {
        coins.push_back(v);
      }
    }
  }

 public:
  long long findKthSmallest(vector<int>& coins_, ll k) {
    Fix(coins_);
    n = coins.size();
    printf("n=%d\n", n);
    for (auto v : coins) {
      printf("%d ", v);
    }
    printf("\n");

    ll l = 1;
    ll r = coins.front() * k + 1;  // [l, r)
    while (l < r) {
      ll mid = (l + r) / 2;
      int K = rongchi(0, mid);
      if (K < k) {
        l = mid + 1;  // 不够，肯定在右边
      } else if (K > k) {
        r = mid - 1;  // 超了，肯定在左边
      } else {
        r = mid;  // 相等，可能是答案，也可能在左边
      }
    }
    return r;
  }
};