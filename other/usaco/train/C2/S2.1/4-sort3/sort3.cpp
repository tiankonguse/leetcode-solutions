/*
ID: tiankonguse
TASK: sort3
LANG: C++
*/
#define TASK "sort3"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<ll> nums;
vector<ll> v123;
vector<vector<ll>> g;

void Solver() {  //
  scanf("%lld", &n);
  nums.resize(n);

  v123.resize(3);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
    nums[i]--;
    v123[nums[i]]++;
  }
  //   for (ll i = 0; i < 3; i++) {
  //     printf("%lld -> %lld\n", i, v123[i]);
  //   }

  g.resize(3, vector<ll>(3, 0));
  const ll pre = v123[0];
  const ll mid = v123[1];
  const ll sub = v123[2];
  for (int i = 0; i < n; i++) {
    const ll v = nums[i];
    if (i < pre) {
      g[0][v]++;
    } else if (i < pre + mid) {
      g[1][v]++;
    } else {
      g[2][v]++;
    }
  }
  //   for (ll i = 0; i < 3; i++) {
  //     printf("i=%lld ", i);
  //     for (ll j = 0; j < 3; j++) {
  //       printf(" %lld", g[i][j]);
  //     }
  //     printf("\n");
  //   }

  ll ans = 0;
  for (ll i = 0; i < 3; i++) {
    for (ll j = i + 1; j < 3; j++) {
      if (g[i][j] > 0 && g[j][i] > 0) {
        const ll swap = min(g[i][j], g[j][i]);
        // printf("swap %lld<-->%lld num=%lld\n", i, j, swap);
        ans += swap;
        g[i][j] -= swap;
        g[j][i] -= swap;
      }
    }
  }
  //   printf("left: 1:%lld 2:%lld\n", g[0][1], g[0][2]);
  ans += max(g[0][1], g[0][2]) * 2;
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
