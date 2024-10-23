/*
ID: tiankonguse
TASK: nocows
LANG: C++
*/
#define TASK "nocows"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const ll mod = 9901;

vector<vector<ll>> dp0;
vector<vector<ll>> dp1;

ll Dfs1(const ll n, const ll k) {  // 树
  if (n == 1 && k == 1) return 1;
  if (n < 2 * k - 1) return 0;     // 最小树，不满足要求
  if (k == 1 && n != 1) return 0;  // 高度为1时，节点个数只能是1

  ll& ret = dp1[n][k];
  if (ret != -1) return ret;

  ret = 0;
  for (ll a = 1; a < n; a++) {  // 左子树 a 个
    // 两边都是 k-1
    ret = (ret + Dfs1(a, k - 1) * Dfs1(n - 1 - a, k - 1)) % mod;
    // 一边是 k-1, 一边小于 k-1
    for (int i = 1; i < k - 1; i++) {
      ret = (ret + Dfs1(a, k - 1) * Dfs1(n - 1 - a, i)) % mod;
      ret = (ret + Dfs1(a, i) * Dfs1(n - 1 - a, k - 1)) % mod;
    }
  }
  return ret;
}

ll Dfs0(const ll n, const ll k) {  // 森林
  if (n < 2 * k - 1) return 0;
  ll& ret = dp0[n][k];
  if (ret != -1) return ret;

  ret = Dfs1(n, k);             // 只有一棵树
  for (ll a = 1; a < n; a++) {  // 枚举第一棵树的节点个数
    ret = (ret + Dfs1(a, k) * Dfs0(n - a, k)) % mod;
  }
  return ret;
}

void Solver() {  //
  ll n, k;
  scanf("%lld%lld", &n, &k);
  dp0.resize(n + 1, vector<ll>(k + 1, -1));
  dp1.resize(n + 1, vector<ll>(k + 1, -1));
  printf("%lld\n", Dfs1(n, k));
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
99 15
2365

*/