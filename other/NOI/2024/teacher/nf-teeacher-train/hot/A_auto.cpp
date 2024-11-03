#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll Test() {
  pair<ll, ll> p = {1, 2};
  auto [x, y] = p;
  auto z = x + y;

  vector<pair<ll, ll>> nums(3, p);
  for (auto [X, Y] : nums) {
    z += X * Y;
  }
  return z;
}

int main() {
  Test();
  ll a, b, c;
  scanf("%lld%lld%lld", &a, &b, &c);
  printf("%.3f\n", (a + b + c) / 3.0);
  return 0;
}