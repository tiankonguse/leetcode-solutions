/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "D"
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

int t;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
}

ll n, m, k;
ll nums[222][222];
ll dp[222][222][222];

inline ll Dis(int a, int b) {  // a -> b
  if (a >= b) {
    return (a - b) * k;
  } else {
    return (m - (b - a)) * k;
  }
}

ll SolverEx(ll) {
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      ll nextMin = INFL;
      if (i < n - 1) {
        for (int o = 0; o < m; o++) {
          nextMin = min(nextMin, dp[i + 1][j][o]);
        }
      }

      for (int o = 0; o < m; o++) {
        if (i == n - 1 && j == m - 1) {
          dp[i][j][o] = Dis(o, j) + nums[i][o];  // 不能走
        }
        if (j < m - 1) {  // 往右走, 右边确定 shift 代价
          ll tmp = nums[i][o] + dp[i][j + 1][(o + 1) % m];
          dp[i][j][o] = min(dp[i][j][o], tmp);
        }
        if (i < n - 1) {  // 往下走
          ll tmp = nums[i][o] + Dis(o, j) + nextMin;
          dp[i][j][o] = min(dp[i][j][o], tmp);
        }
      }
    }
  }
  ll nextMin = INFL;
  for (int o = 0; o < m; o++) {
    nextMin = min(nextMin, dp[0][0][o]);
  }
  return nextMin;
}
void Solver() {  //
  while (t--) {
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%lld", &nums[i][j]);
        for (int o = 0; o < m; o++) {
          dp[i][j][o] = INFL;  // 初始化
        }
      }
    }
    printf("%lld\n", SolverEx(0));
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
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