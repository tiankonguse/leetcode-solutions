/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "C-v22"
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

const ll mod = 2933256077ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

const int N = 3e6 + 10;
int n, m;
char str[N];
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d%s", &n, &m, str);
}

ll dp[222][111][111];  // f(p, nn, mm) 前 p 个匹配，剩余  mm 个 0 与 nn 个 1 时的最优答案
void Solver() {        //
  memset(dp, 0, sizeof(dp));
  // 递归修改为递推
  for (int ni = 0; ni <= n; ni++) {
    for (int mi = 0; mi <= m; mi++) {
      dp[n + m][ni][mi] = n + m;
    }
  }
  for (int i = n + m - 1; i >= 0; i--) {
    const int v = str[i] - '0';
    if (v == 0) {
      for (int ni = 0, mi = 0; ni <= n && i + ni + mi <= n + m; ni++) {
        dp[i][mi][ni] = i;  // mi = 0
      }
      for (int mi = 1; mi <= m && i + mi <= n + m; mi++) {
        dp[i][mi][0] = dp[i + 1][mi - 1][0];  // ni = 0
        for (int ni = 1; ni <= n && i + ni + mi <= n + m; ni++) {
          dp[i][mi][ni] = (dp[i][mi][ni - 1] + dp[i + 1][mi - 1][ni]) % mod;
        }
      }
    } else {
      for (int mi = 0, ni = 0; mi <= m && i + ni + mi <= n + m; mi++) {
        dp[i][mi][ni] = i;  // ni = 0
      }
      for (int ni = 1; ni <= n && i + ni <= n + m; ni++) {
        dp[i][0][ni] = dp[i + 1][0][ni - 1];  // mi = 0
        for (int mi = 1; mi <= m && i + ni + mi <= n + m; mi++) {
          dp[i][mi][ni] = (dp[i][mi - 1][ni] + dp[i + 1][mi][ni - 1]) % mod;
        }
      }
    }
  }
  // for (int i = 0; i < n + m; i++) {
  //   for (int ni = 0; ni <= n; ni++) {
  //     for (int mi = 0; mi <= m; mi++) {
  //       printf("[%d,%d,%d]=%lld\n", i, ni, mi, dp[i][mi][ni]);
  //     }
  //   }
  // }
  printf("%lld\n", dp[0][m][n]);
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