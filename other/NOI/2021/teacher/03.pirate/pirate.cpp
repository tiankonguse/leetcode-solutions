
/*
ID: tiankonguse
TASK: pirate
LANG: C++
CONTEST: 2021 年 CCF NOI线上教师培训测试
OJ:
*/
#define TASK "pirate"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

ll n;
vector<ll> nums;
vector<vector<ll>> g;
ll ans = 0;

ll sum = 0;
vector<ll> sums;  // 子树节点和

ll Dfs(ll u, ll dep, ll pre = -1) {
  ll ans = nums[u] * dep;
  sums[u] = nums[u];
  for (ll v : g[u]) {
    if (v == pre) continue;
    ans += Dfs(v, dep + 1, u);
    sums[u] += sums[v];
  }
  return ans;
}
void DfsDp(ll u, ll preSum, ll pre = -1) {
  ll tmpAns = 0;
  if (pre == -1) {
    tmpAns = preSum;
  } else {
    tmpAns = preSum - sums[u] + (sum - sums[u]);
  }
  ans = max(ans, tmpAns);
  for (ll v : g[u]) {
    if (v == pre) continue;
    DfsDp(v, tmpAns, u);
  }
}

void Solver() {  //
  scanf("%lld", &n);
  nums.resize(n);
  g.resize(n);
  sums.resize(n, 0);

  for (ll i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
    sum += nums[i];
  }
  for (ll i = 1; i < n; i++) {
    ll u, v;
    scanf("%lld%lld", &u, &v);
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ans = Dfs(0, 0);
  DfsDp(0, ans);
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
9 4 1 7 10 1 6 5
1 2
2 3
1 4
1 5
5 6
5 7
5 8

121
*/