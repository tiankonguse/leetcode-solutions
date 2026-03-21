/*
ID: tiankonguse
TASK: scarf-cutting
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "scarf-cutting"
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
// #define LOCAL_IO 0
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int n, n2;
int m;
const int N = 205;  // 开够
int dp[N][N];
int points[N][N];
vector<int> dpUpMax;
vector<int> dpDownMax;
inline bool OK(const int x, const int y) {  // 0-based
  return x >= 0 && x < n && y >= 0 && y < 2 * x + 1;
}
void SolverUp() {
  // points 内存大小为 [n][n2]
  const int n2 = n * 2 - 1;
  for (int i = 0; i < n; i++) {
    const int ni = i * 2 + 1;
    dpUpMax[i] = 0;
    for (int j = 0; j < ni; j++) {
      dp[i][j] = 0;
      if (points[i][j] == 0) continue;
      dp[i][j] = 1;
      if (j % 2 == 0) {  // 正三角形
        // 左边和左上的最小正三角
        if (OK(i - 1, j - 2) && OK(i, j - 2) && points[i][j - 1] == 1) {
          int leftVal = dp[i][j - 2];
          int upVal = dp[i - 1][j - 2];
          dp[i][j] = min(leftVal, upVal) + 1;
        }
      } else {  // 倒三角形
        // 左上与右上的最小倒三角
        if (OK(i - 1, j - 2) && OK(i - 1, j) && points[i - 1][j - 1] == 1) {
          int leftVal = dp[i - 1][j - 2];
          int rightVal = dp[i - 1][j];
          dp[i][j] = min(leftVal, rightVal) + 1;
        }
      }
      dpUpMax[i] = max(dpUpMax[i], dp[i][j]);
    }
  }
  for (int i = 1; i < n; i++) {
    dpUpMax[i] = max(dpUpMax[i], dpUpMax[i - 1]);
  }
}

void SolverDown() {
  // points 内存大小为 [n][n2]
  const int n2 = n * 2 - 1;

  for (int i = n - 1; i >= 0; i--) {
    dpDownMax[i] = 0;
    const int ni = i * 2 + 1;
    for (int j = 0; j < ni; j++) {
      dp[i][j] = 0;
      if (points[i][j] == 0) continue;
      dp[i][j] = 1;
      if (j % 2 == 0) {  // 正三角形
        // 左下与右下的最小正三角
        if (OK(i + 1, j) && OK(i + 1, j + 2) && points[i + 1][j + 1] == 1) {
          int leftVal = dp[i + 1][j];
          int rightVal = dp[i + 1][j + 2];
          dp[i][j] = min(leftVal, rightVal) + 1;
        }
      } else {  // 倒三角形
        // 左边和左下的最小倒三角
        if (OK(i, j - 2) && OK(i + 1, j) && points[i][j - 1] == 1) {
          int leftVal = dp[i][j - 2];
          int downVal = dp[i + 1][j];
          dp[i][j] = min(leftVal, downVal) + 1;
        }
      }
      dpDownMax[i] = max(dpDownMax[i], dp[i][j]);
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    dpDownMax[i] = max(dpDownMax[i], dpDownMax[i + 1]);
  }
}

vector<pair<int, int>> basePoints;  // 0-based
int SolverOne() {
  // 只需要处理上下分割线即可
  for (int i = 0; i < m; i++) {
    auto [x, y] = basePoints[i];
    points[x][y] = 0;
  }
  SolverUp();
  SolverDown();
  int ans = 0;
  for (int i = 0; i + 1 < n; i++) {
    int upVal = dpUpMax[i];
    int downVal = dpDownMax[i + 1];
    if (upVal > 0 && downVal > 0) {
      ans = max(ans, upVal * upVal + downVal * downVal);
    }
  }
  for (int i = 0; i < m; i++) {
    auto [x, y] = basePoints[i];
    points[x][y] = 1;  // 还原默认值
  }
  return ans;
}
pair<int, int> Rotate(const int n, const int x0, const int y0) {
  const int x1 = n - 1 - y0 / 2;
  const int y1 = 2 * x0 - y0;
  return {x1, y1};
}
void Rotate(const int n) {
  // 第 0 行有 1 个小三角形
  // 第 1 行有 3 个小三角形
  // 第 2 行有 5 个小三角形
  // ...
  // 第 n 行有 2n + 1 个小三角形
  // 逆时针旋转 90 度
  // x1 = n - 1 - y0 / 2;
  // y1 = 2 * x0 - y0;
  for (int i = 0; i < m; i++) {
    auto [x0, y0] = basePoints[i];
    MyAssert(x0 >= 0 && x0 < n && y0 >= 0 && y0 < 2 * x0 + 1);
    auto [x1, y1] = Rotate(n, x0, y0);
    basePoints[i] = {x1, y1};
    MyAssert(x1 >= 0 && x1 < n && y1 >= 0 && y1 < 2 * x1 + 1);
  }
}

void Test() {
  // for(int p=2;p<=100;p++){
  //   MyPrintf("p=%d\n", p);
  //   for(int i=0;i<p;i++){
  //     for(int j=0;j<2*i+1;j++){
  //       const int x0 = i;
  //       const int y0 = j;
  //       const auto [x1, y1] = Rotate(p, x0, y0);
  //       assert(x1 >= 0 && x1 < p && y1 >= 0 && y1 < 2 * p - 1);
  //     }
  //   }
  // }
}

void Solver() {  //
  scanf("%d", &n);
  n2 = n * 2 - 1;
  for (int i = 0; i < N; i++) {
    fill(points[i], points[i] + N, 1);
    fill(dp[i], dp[i] + N, 0);
  }
  dpUpMax.resize(n, 0);
  dpDownMax.resize(n, 0);

  scanf("%d", &m);
  basePoints.resize(m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);  // 1-based
    int x1 = x - 1;
    int y1 = y - 1;
    MyAssert(x1 >= 0 && x1 < n && y1 >= 0 && y1 < 2 * x1 + 1);
    basePoints[i] = {x1, y1};  // 0-based
  }
  if (n == 1) {
    printf("0\n");
    return;
  }
  int ans = SolverOne();
  for (int i = 0; i < 2; i++) {
    Rotate(n);
    ans = max(ans, SolverOne());
  }
  printf("%d\n", ans);
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
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  MyPrintf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
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
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
