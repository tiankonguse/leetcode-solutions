/*
ID: tiankonguse
TASK: explore
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11227?contestId=209924
*/
#define TASK "explore"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

ll n, k, q;
vector<vector<ll>> nums;
vector<vector<ll>> dp;
vector<pair<ll, ll>> querys;
ll R;
ll sum = 0;

void Solver() {  //
  ll t;
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld%lld", &n, &k, &q);
    nums.resize(n);
    sum = 0;
    for (int i = 0; i < n; i++) {
      ll l;
      scanf("%lld", &l);
      sum += l;
      nums[i].resize(l);
      for (int j = 0; j < l; j++) {
        ll S;
        scanf("%lld", &S);
        nums[i][j] = S;
      }
    }

    querys.resize(q);
    R = 1;
    for (int i = 0; i < q; i++) {
      scanf("%lld%lld", &querys[i].first, &querys[i].second);
      R = max(R, querys[i].first);
    }

    dp.clear();
    dp.resize(R + 1, vector<ll>(sum + 1, -1));

    unordered_map<ll, ll> pre;
    unordered_map<ll, ll> now;
    vector<unordered_map<ll, ll>> H;

    auto IsBegin = [](int i, int l) -> bool {  //
      return 0;
    };

    H.resize(n);
    pre[1] = sum + 1;
    for (int r = 1; r <= R; r++) {   // 进行 R 轮游戏
      for (int i = 0; i < n; i++) {  // n 个序列
        now.clear();
        int l = 0, r = 0;
        for (int l = 0; l + 1 < nums[i].size(); l++) {
          if (IsBegin(i, l)) {
          }
          const ll v = nums[i][l];
          ll vc = H[i][v];
          if (pre.count(v) && pre[v] > vc) {  // 其他行尾部有 v，可以选择 v
          }
        }
      }
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
5 5
*/