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

const int mod = 9901;

vector<vector<int>> dp1;

int Dfs1(const int n, const int k) {  // 树
  auto& ret = dp1[n][k];
  if (ret != -1) return ret;
  ret = 0;

  for (int a = 1; a < n; a += 2) {  // 左子树 a 个
    const int b = n - 1 - a;
    // 两边都是 k-1
    ret = (ret + Dfs1(a, k - 1) * Dfs1(b, k - 1)) % mod;
    // 一边是 k-1, 一边小于 k-1
    for (int i = 1; i < k - 1; i++) {
      ret = (ret + 2 * Dfs1(a, k - 1) * Dfs1(b, i)) % mod;
      //   ret = (ret + Dfs1(a, i) * Dfs1(b, k - 1)) % mod;
    }
  }
  return ret;
}

int n, k;
void Init() {
  dp1.resize(n + 1, vector<int>(k + 1, -1));  //
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      auto& ret = dp1[i][j];
      if (i < 1 || j < 1 || i < 2 * j - 1 || i % 2 == 0) {
        ret = 0;
        continue;
      }
      if (i == 1) {
        if (j == 1) {
          ret = 1;
        } else {
          ret = 0;
        }
      }
    }
  }
}

void Solver() {  //
  scanf("%d%d", &n, &k);
  Init();
  printf("%d\n", Dfs1(n, k));
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
99 15
2365

172 44
0

199 99
1808
*/