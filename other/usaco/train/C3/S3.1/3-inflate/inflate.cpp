/*
ID: tiankonguse
TASK: inflate
LANG: C++
*/
#define TASK "inflate"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int m, n;
vector<pair<int, int>> nums;
vector<int> V;
void Solver() {  //
  scanf("%d%d", &m, &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &nums[i].second, &nums[i].first);
  }
  sort(nums.begin(), nums.end());

  V.resize(m + 1, 0);

  for (int v = 0; v < m; v++) {
    for (int j = 0; j < n && v + nums[j].first <= m; j++) {
      int newV = v + nums[j].first;
      V[newV] = max(V[newV], V[v] + nums[j].second);
    }
  }
  printf("%d\n", V[m]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/