/*
ID: tiankonguse
TASK: number
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7074
PATH:  P7074 [CSP-J2020] 方格取数
submission:
*/
#define TASK "number"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// #define TASKNO "4"
//   freopen(TASK TASKNO ".in", "r", stdin);
//   freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

void Solver() {  //
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<ll>> a(n + 1, vector<ll>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%lld", &a[i][j]);
    }
  }
  vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -INFL));
  dp[0][1] = 0;
  for (int i = 1; i <= n; i++) {
    dp[i][1] = a[i][1] + dp[i - 1][1];
  }
  for (int j = 2; j <= m; j++) {
    // 从上到下
    ll maxValue = -INFL;
    for (int i = 1; i <= n; i++) {
      maxValue = max(maxValue, dp[i][j - 1]) + a[i][j];
      dp[i][j] = max(dp[i][j], maxValue);
    }
    maxValue = ninf;
    for (int i = n; i >= 1; i--) {
      maxValue = max(maxValue, dp[i][j - 1]) + a[i][j];
      dp[i][j] = max(dp[i][j], maxValue);
    }
  }
  printf("%lld\n", dp[n][m]);
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/