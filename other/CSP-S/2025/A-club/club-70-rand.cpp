/*
ID: tiankonguse
TASK: club
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "club"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
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

void InitIO(int fileIndex) {  //
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#ifdef LOCAL_IO
#define USACO_TASK_FILE 1
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int n;
ll dp[202][202][202];  // dp[i][a][b]  前 i 个人中，A 组选择 a 个，B 组选择 b 个的方案数
const int maxn = 1e5 + 10;
vector<tuple<ll, ll, ll>> a;  // a[i] = {a1,a2,a3}

void SolverDp() {
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll a1, a2, a3;
    scanf("%lld%lld%lld", &a1, &a2, &a3);
    // 共 i 个人
    for (int a = 0; a <= i; a++) {
      if (a > n / 2) continue;
      for (int b = 0; b <= i; b++) {
        int c = i - a - b;
        if (b > n / 2 || c < 0 || c > n / 2) continue;
        dp[i][a][b] = 0;
        // 选择 A 组
        if (a > 0 && dp[i - 1][a - 1][b] != -1) {
          dp[i][a][b] = max(dp[i - 1][a - 1][b] + a1, dp[i][a][b]);
        }
        // 选择 B 组
        if (b > 0 && dp[i - 1][a][b - 1] != -1) {
          dp[i][a][b] = max(dp[i - 1][a][b - 1] + a2, dp[i][a][b]);
        }
        // 选择 C 组
        if (c > 0 && dp[i - 1][a][b] != -1) {
          dp[i][a][b] = max(dp[i - 1][a][b] + a3, dp[i][a][b]);
        }
        if (i == n && dp[i][a][b] != -1) {
          ans = max(ans, dp[i][a][b]);
        }
      }
    }
  }
  printf("%lld\n", ans);
}
void Solver() {  //
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    if (n <= 200) {
      SolverDp();
      continue;
    }
    // 先输入数据
    ll sum1 = 0, sum2 = 0, sum3 = 0;
    a.clear();
    a.reserve(n);
    for (int i = 0; i < n; i++) {
      ll a1, a2, a3;
      scanf("%lld%lld%lld", &a1, &a2, &a3);
      a.push_back({a1, a2, a3});
      sum1 += a1;
      sum2 += a2;
      sum3 += a3;
    }
    if (sum2 == 0 && sum3 == 0) {  // 特殊性质 A: a2 和 a3 全为 0
      // a1 中选择最大的 n/2 个，其他选 0
      sort(a.begin(), a.end(), greater<tuple<ll, ll, ll>>());
      ll ans = 0;
      for (int i = 0; i < n / 2; i++) {
        ans += get<0>(a[i]);
      }
      printf("%lld\n", ans);
      continue;
    }
    if (sum3 == 0) {
      // 特殊性质 B： a3 全为 0
      // 暂时没想到更高的算法，所以进行随机化处理
      ll ans = 0;
      for (auto& [a1, a2, a3] : a) {
        // 贪心肯定有反例的，所以增加一个随机因子
        if (rand() % 2) {
          ans += a1;
        } else {
          ans += a2;
        }
      }
      printf("%lld\n", ans);
      continue;
    }

    // 特殊性质 C：贪心选择
    ll ans = 0;
    for (auto& [a1, a2, a3] : a) {
      if (a1 >= a2 && a1 >= a3) {
        ans += a1;
      } else if (a2 >= a1 && a2 >= a3) {
        ans += a2;
      } else {
        ans += a3;
      }
    }
    printf("%lld\n", ans);
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
  }
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
    string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
    string fileOut = string(TASK) + to_string(fileIndex) + ".out";
    string cmd = string("diff -w " + fileAns + " " + fileOut);
    if (system(cmd.c_str())) {
      printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
    } else {
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
#endif
  return 0;
}
