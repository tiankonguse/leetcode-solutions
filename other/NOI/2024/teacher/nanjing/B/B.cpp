#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
2a+1
4a+4
*/
ll Solver(ll r) {          // [0,r] 之间的非答案个数
  ll ans = r / 4;          // 至少的答案个数
  if (ans * 4 + 2 <= r) {  //
    ans++;
  }
  return ans;
}
ll Solver(ll l, ll r) {  // [l,r] 之间的答案
  ll ans = r - l + 1;
  ans = ans - (Solver(r) - Solver(l - 1));
  return ans;
}
int main() {
  ll Q;
  scanf("%lld", &Q);
  while (Q--) {
    ll l, r;
    scanf("%lld%lld", &l, &r);
    ll ans = 0;
    // l <= r
    if (r <= 0) {  // l <=r <=0
      ans = Solver(-r, -l);
    } else if (l < 0) {  // l < 0 < r
      ans = Solver(1, -l) + Solver(0, r);
    } else {  // 0 <= l <= r
      ans = Solver(l, r);
    }
    printf("%lld\n", ans);
  }
  return 0;
}