/*
ID: tiankonguse
TASK: sprime
LANG: C++
*/
#define TASK "sprime"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
const int N = 20001;
const int M = 2272;
bitset<N> bits;
int prm[M];
int K;
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
  return K = k;
}

ll n;
vector<ll> ans;

bool Check(const ll v) {
  if (v < N) {
    return !bits.test(v);
  }
  ll e = (ll)(sqrt(0.0 + v) + 1);
  for (int i = 0; i < K && prm[i] <= e; i++) {
    if (v % prm[i] == 0) {
      return false;
    }
  }
  return true;
}

void Dfs(const ll pre, const ll bit) {
  if (bit == n) {
    ans.push_back(pre);
    return;
  }
  for (int i = 1; i <= 9; i += 2) {
    ll v = pre * 10 + i;
    if (Check(v)) {
      Dfs(v, bit + 1);
    }
  }
}

void Solver() {  //
  ll k = getprm();
  // printf("k=%lld\n", k);
  // printf("last %d\n", prm[k - 1]);

  scanf("%lld", &n);
  Dfs(2, 1);
  Dfs(3, 1);
  Dfs(5, 1);
  Dfs(7, 1);

  for (ll v : ans) {
    printf("%lld\n", v);
  }
//   printf("size=%lld\n", ans.size());
}

int main() {
  InitIO();
  Solver();
  return 0;
}
