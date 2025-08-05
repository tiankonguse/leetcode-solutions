/*
ID: tiankonguse
TASK: traffic
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7916
PATH: P7916 [CSP-S 2021] 交通规划
submission:
*/
#define TASK "traffic"
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

int n, m, t;
vector<vector<ll>> vg, hg;

void InitBoard() {
  for (int j = 0; j <= m + 1; j++) {
    vg[0][j] = vg[n][j] = 0;
  }
  for (int i = 0; i <= n + 1; i++) {
    vg[i][0] = vg[i][m] = 0;
  }
}

void Solver() {  //
  scanf("%d%d%d", &n, &m, &t);
  vg.resize(n + 2, vector<ll>(m + 2, 0));
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%lld", &vg[i][j]);
    }
  }
  hg.resize(m + 2, vector<ll>(n + 2, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      scanf("%lld", &hg[i][j]);
    }
  }
  while (t--) {
    InitBoard();
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
      int x, p, c;  // 第 p 个点，边权是 x，颜色是 c
      scanf("%d%d%d", &x, &p, &c);
    }
  }
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