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

bool Check(ll v) {
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

void Solver() {  //
  ll k = getprm();
  // printf("k=%lld\n", k);
  // printf("last %d\n", prm[k - 1]);

  ll a, b;
  scanf("%lld%lld", &a, &b);

  vector<ll> ans;
  ans.reserve(100000);
  for (int i = 5; i < 10; i++) {
    ll pre = i;
    if (pre >= a && pre <= b && Check(pre)) {
      ans.push_back(pre);
    }
  }
  for (ll i = 1; i < 10000; i++) {
    // 偶数位
    ll pre = i;
    ll tmp = i;
    while (tmp) {
      pre = pre * 10 + (tmp % 10);
      tmp = tmp / 10;
    }
    if (pre >= a && pre <= b && Check(pre)) {
      ans.push_back(pre);
    }
    if (pre > b) break;
  }
  for (ll i = 1; i < 10000; i++) {
    // 奇数位
    ll firstPre = 0;
    for (int j = 0; j < 10; j++) {
      ll pre = i * 10 + j;
      ll tmp = i;
      while (tmp) {
        pre = pre * 10 + (tmp % 10);
        tmp = tmp / 10;
      }
      if (pre >= a && pre <= b && Check(pre)) {
        ans.push_back(pre);
      }
      if (firstPre == 0) {
        firstPre = pre;
      }
    }
    if (firstPre > b) break;
  }

  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
