/*
ID: tiankonguse
TASK: uqe
LANG: C++
CONTEST: CSP-J 2023
OJ: https://qoj.ac/contest/1427/problem/7811
*/
#define TASK "uqe"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

/*
 */

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}

ll a, b, c;
void Fix() {
  ll k = abs(Gcd(Gcd(a, b), c));
  if (a < 0) {
    k = -k;
  }
  a /= k;
  b /= k;
  c /= k;
}
void output(ll p, ll q) {
  ll k = abs(gcd(p, q));
  p /= k;
  q /= k;
  if (q == 1) {
    printf("%lld", p);
  } else {
    printf("%lld/%lld", p, q);
  }
}
ll sqrFactor(ll sq, ll d) {
  for (ll i = sq; i >= 1; i--) {
    if (d % (i * i) == 0) {
      return i;
    }
  }
  return 1;
}
void RealSolver() {
  Fix();

  ll d = b * b - 4 * a * c;
  // printf("a=%lld b=%lld c=%lld d=%lld\n", a, b, c, d);

  if (d < 0) {  // 无解
    printf("NO\n");
    return;
  }

  if (d == 0) {
    output(-b, 2 * a);  // 一个解
    printf("\n");
    return;
  }

  // 有两个解
  ll sq = sqrt(d);
  if (sq * sq == d) {        // 有理数解
    output(-b + sq, 2 * a);  // 一个解
    printf("\n");
    return;
  }

  if (b != 0) {
    output(-b, 2 * a);
    printf("+");
  }
  ll p = sqrFactor(sq, d);
  ll q = 2 * a;
  d /= p * p;
  ll k = abs(gcd(p, q));
  p /= k;
  q /= k;
  if (p == 1 && q == 1) {
    printf("sqrt(%lld)\n", d);
  } else if (p > 1 && q == 1) {
    printf("%lld*sqrt(%lld)\n", p, d);
  } else if (p == 1 && q > 1) {
    printf("sqrt(%lld)/%lld\n", d, q);
  } else {
    printf("%d*sqrt(%lld)/%lld\n", p, d, q);
  }
}
void Solver() {  //
  ll t, m;
  scanf("%lld%lld", &t, &m);
  while (t--) {
    scanf("%lld%lld%lld", &a, &b, &c);
    RealSolver();
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
9 1000
1 ‐1 0
‐1 ‐1 ‐1
1 ‐2 1
1 5 4
4 4 1
1 0 ‐432
1 ‐3 1
2 ‐4 1
1 7 1

1
NO
1
‐1
‐1/2
12*sqrt(3)
3/2+sqrt(5)/2
1+sqrt(2)/2
‐7/2+3*sqrt(5)/2
*/