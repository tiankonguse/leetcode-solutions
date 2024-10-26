/*
ID: tiankonguse
TASK: concom
LANG: C++
*/
#define TASK "concom"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const ll N = 101;
ll n;
vector<vector<ll>> base;

vector<ll> flag;  // 是否已经控股这个公司
vector<ll> sums;  // 当前节点拥有的各个公司的股份之和
void Solver(const int a) {
  flag.clear();
  flag.resize(N, 0);
  sums.clear();
  sums.resize(N, 0);
  queue<int> que;
  que.push(a);
  flag[a] = 1;

  while (!que.empty()) {
    int b = que.front();
    que.pop();
    for (int i = 1; i < N; i++) {  // 控股 b 公司， b 公司的股份传累加到 a 公司
      sums[i] += base[b][i];
      if (sums[i] > 50 && flag[i] == 0) {
        flag[i] = 1;
        base[a][i] = 100;  // a 控股 i 公司
        que.push(i);
      }
    }
  }
}

void Solver() {  //

  base.resize(N, vector<ll>(N, 0));
  scanf("%lld", &n);
  while (n--) {
    ll i, j, p;
    scanf("%lld%lld%lld", &i, &j, &p);
    base[i][j] = p;
  }
  for (ll i = 1; i < N; i++) {
    Solver(i);
    for (ll j = 1; j < N; j++) {
      if (j == i) continue;
      if (base[i][j] == 100) {
        printf("%lld %lld\n", i, j);
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
3
1 2 80
2 3 80
3 1 20

1 2
1 3
2 3
*/