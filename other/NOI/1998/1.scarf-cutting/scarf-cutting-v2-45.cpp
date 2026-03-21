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

int n;
int m;
vector<pair<int, int>> basePoints;  // 0-based
vector<int> dpUpMax, dpDownMax;
void SolverUp(const vector<vector<int>>& points) {
  const int n2 = n * 2 + 1;
  vector<vector<int>> dpUp(n, vector<int>(n2 + 2, 0));
  dpUpMax.resize(n, 0);
  fill(dpUpMax.begin(), dpUpMax.end(), 0);

  for (int i = 0; i < n; i++) {
    const int ni = i * 2 + 1;
    for (int j = 0; j < ni; j++) {
      if (points[i][j] == 0) continue;
      dpUp[i][j] = 1;
      if (j % 2 == 0) {  // 正三角形
        if (i - 1 >= 0 && j - 1 >= 0 && points[i][j - 1] == 1 && j - 2 >= 0) {
          int leftVal = dpUp[i][j - 2];
          int upVal = dpUp[i - 1][j - 2];
          dpUp[i][j] = min(leftVal, upVal) + 1;
        }
      } else {  // 倒三角形
        if (i - 1 >= 0 && j - 1 >= 0 && points[i - 1][j - 1] == 1 && j - 2 >= 0) {
          int leftVal = dpUp[i - 1][j - 2];
          int rightVal = dpUp[i - 1][j];
          dpUp[i][j] = min(leftVal, rightVal) + 1;
        }
      }
      dpUpMax[i] = max(dpUpMax[i], dpUp[i][j]);
    }
  }
}
void SolverDown(const vector<vector<int>>& points) {
  const int n2 = n * 2 + 1;
  vector<vector<int>> dpDown(n + 1, vector<int>(n2 + 2, 0));
  dpDownMax.resize(n + 1, 0);
  fill(dpDownMax.begin(), dpDownMax.end(), 0);

  for (int i = n - 1; i >= 0; i--) {
    const int ni = i * 2 + 1;
    for (int j = 0; j < ni; j++) {
      if (points[i][j] == 0) continue;
      dpDown[i][j] = 1;

      if (j % 2 == 0) {  // 正三角形
        if (i + 1 < n && j + 1 < n2 && points[i][j + 1] == 1 && j + 2 < n2) {
          int leftVal = dpDown[i + 1][j];
          int rightVal = dpDown[i + 1][j + 2];
          dpDown[i][j] = min(leftVal, rightVal) + 1;
        }
      } else {  // 倒三角形
        if (i + 1 < n && j - 1 >= 0 && points[i][j - 1] == 1 && j - 2 >= 0) {
          int leftVal = dpDown[i][j - 2];
          int downVal = dpDown[i + 1][j];
          dpDown[i][j] = min(leftVal, downVal) + 1;
        }
      }
      dpDownMax[i] = max(dpDownMax[i], dpDown[i][j]);
    }
  }
}
int SolverOne() {
  // 只需要处理上下分割线即可
  const int n2 = n * 2 + 1;
  vector<vector<int>> points(n, vector<int>(n2, 1));
  for (auto& [x, y] : basePoints) {
    points[x][y] = 0;
  }
  SolverUp(points);
  SolverDown(points);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int upVal = dpUpMax[i];
    int downVal = dpDownMax[i + 1];
    if (upVal > 0 && downVal > 0) {
      ans = max(ans, upVal * upVal + downVal * downVal);
    }
  }
  return ans;
}
void Rotate() {
  // x1 = n - 1 - y0 / 2;
  // y1 = 2 * x0 - y0;
  for (auto& [x0, y0] : basePoints) {
    int x1 = n - 1 - y0 / 2;
    int y1 = 2 * x0 - y0;
    x0 = x1;
    y0 = y1;
  }
}

void Solver() {  //
  scanf("%d", &n);
  scanf("%d", &m);
  basePoints.resize(m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);           // 1-based
    basePoints[i] = {x - 1, y - 1};  // 0-based
  }
  int ans = 2;
  for (int i = 0; i < 3; i++) {
    ans = max(ans, SolverOne());
    Rotate();
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
  printf("my 用时: %.0lfms\n", costTime);
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
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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
