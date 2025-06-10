/*
ID: tiankonguse
TASK: color
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P11233?contestId=209925
PATH: P11233 [CSP-S 2024] 染色
submission:
*/
#define TASK "color"
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
//   freopen(TASK ".out", "w", stdout);
#endif
}

const int N = 2e5 + 10;
const int V = 1e6 + 10;
int n;
ll A[N];
ll dp[2][N];
ll B[N];   // 记录前缀颜色全部相同时，前缀的答案
int H[V];  // 记录值为 V 的最后一个位置, 0 代表没有出现过
int P[N];  // 与 A[i] 相等的上一个位置

ll Range(int l, int r) {
  if (l >= r) return 0;
  return B[r] - B[l];
}

ll Dfs(int color, int pos) {
  if (pos == 0) return 0;
  if (dp[color][pos] != -1) return dp[color][pos];

  // pos 分为得分与不得分
  ll ans = max(Dfs(color, pos - 1), Dfs(color ^ 1, pos - 1));
  if (P[pos] != 0) {
    int lastPos = P[pos];
    ll tmp = A[pos] + Range(lastPos + 1, pos - 1);
    if (lastPos + 1 != pos) {
      tmp += Dfs(color ^ 1, lastPos + 1);
    } else {
      tmp += Dfs(color, lastPos);
    }
    ans = max(ans, tmp);
  }

  return dp[color][pos] = ans;
}

void Solver() {  //
  int t = 0;
  scanf("%d", &t);
  A[0] = 0;  // A[0] 不参与计算, 设置为一个不存在的值
  while (t--) {
    memset(H, 0, sizeof(H));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &A[i]);
    }
    for (int i = 1; i <= n; i++) {
      ll v = A[i];

      P[i] = H[v];  // 记录与 A[i] 相等的上一个位置
      H[v] = i;     // 记录值为 A[i] 的最后一个位置
      if (v == A[i - 1]) {
        B[i] = B[i - 1] + v;
      } else {
        B[i] = B[i - 1];
      }
    //   printf("i=%d P=%d B=%lld\n", i, P[i], B[i]);
    }
    // 初始化 dp 数组
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", max(Dfs(0, n), Dfs(1, n)));
    // for (int i = 0; i <= n; i++) {
    //   printf("dp[0][%d]=%lld dp[1][%d]=%lld\n", i, dp[0][i], i, dp[1][i]);
    // }
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