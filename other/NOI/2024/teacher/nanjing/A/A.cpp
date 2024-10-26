#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  ll a, b;
  ll x, y, z;
  scanf("%lld%lld", &a, &b);
  scanf("%lld%lld%lld", &x, &y, &z);

  ll ans = 0;
  a -= x * 2;
  a -= y;
  b -= y;
  b -= z * 3;
  if (a < 0) {
    ans -= a;
  }
  if (b < 0) {
    ans -= b;
  }
  printf("%lld\n", ans);

  return 0;
}