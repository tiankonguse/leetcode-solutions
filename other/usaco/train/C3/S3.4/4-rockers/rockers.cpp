/*
ID: tiankonguse
TASK: rockers
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "rockers"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int nums[22];
int dp[22][22];
int dp2[22][22][22];
int T;

int Dfs2(int l, int r, int t) {  // [l,r]
  if (t == 0 || r < l) return 0;
  int& ret = dp2[l][r][t];
  if (ret != -1) return ret;

  ret = Dfs2(l, r - 1, t);  // 不选择
  if (nums[r] <= t) {
    ret = max(ret, 1 + Dfs2(l, r - 1, t - nums[r]));
  }
  return ret;
}

int Dfs(int n, int m) { // [0,n][1,m]
  if (n < 0 || m <= 0) return 0;
  int& ret = dp[n][m];
  if (ret != -1) return ret;

  ret = 0;
  for (int i = 0; i <= n; i++) {
    ret = max(ret, Dfs(i - 1, m - 1) + Dfs2(i, n, T));
  }
  return ret;
}

void Solver() {  //
  int n, m;
  scanf("%d%d%d", &n, &T, &m);

  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }

  memset(dp2, -1, sizeof(dp2));
  memset(dp, -1, sizeof(dp));
  printf("%d\n", Dfs(n - 1, m));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/