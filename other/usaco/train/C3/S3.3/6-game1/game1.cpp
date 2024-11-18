/*
ID: tiankonguse
TASK: game1
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "game1"

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

const int N = 111;
int n;
int nums[N];
int sums[N];
int dp[N][N];

int Dfs(int l, int r) {
  int& ret = dp[l][r];
  if (ret != 0) return ret;

  int sum = sums[r] - sums[l - 1];
  if (l == r) {
    return ret = sum;
  }
  return ret = sum - min(Dfs(l + 1, r), Dfs(l, r - 1));
}

void Solver() {  //
  scanf("%d", &n);
  sums[0] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &nums[i]);
    sums[i] = sums[i - 1] + nums[i];
  }
  memset(dp, 0, sizeof(dp));

  int ans = Dfs(1, n);
  printf("%d %d\n", ans, sums[n] - ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/