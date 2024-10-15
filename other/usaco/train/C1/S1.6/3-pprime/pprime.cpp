/*
ID: tiankonguse
TASK: pprime
LANG: C++
*/
#define TASK "pprime"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
const int N = 100000001;
const int M = 5761457;
bitset<N> bits;
int prm[M];
int getprm() {
  ll e = (ll)(sqrt(0.0 + N) + 1), k = 0, i;
  prm[k++] = 2;
  bits.set(0);
  bits.set(1);
  for (i = 4; i < N; i += 2) bits.set(i);
  for (i = 3; i < e; i += 2) {
    if (!bits.test(i)) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) bits.set(j);
    }
  }
  for (; i < N; i += 2)
    if (!bits.test(i)) prm[k++] = i;
  return k;
}

void Solver() {  //
  ll k = getprm();
  //     printf("k=%lld\n", k);
  //   printf("last %lld\n", prm[k - 1]);

  ll a, b;
  scanf("%lld%lld", &a, &b);
  ll ap = lower_bound(prm, prm + k, a) - prm;
  ll bp = upper_bound(prm, prm + k, b) - prm;
  for (ll i = ap; i < bp; i++) {
    ll v = prm[i];
    ll V = 0;
    while (v) {
      V = V * 10 + (v % 10);
      v = v / 10;
    }
    if (V == prm[i]) {
      printf("%lld\n", V);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
