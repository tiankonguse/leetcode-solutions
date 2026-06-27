/*
ID: tiankonguse
TASK: grid-number
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1004
PATH:
submission:
*/
#define TASK "grid-number"
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

int N;
int g[11][11];
int dp[11][11][11][11];

/*
    规则1: r0 >= r1，即 点0 不可能在 点1 的上方
    规则2: c0 <= c1，即 点0 不可能在 点1 的右方
    规则3: r0 - r1 <= 1，即 点0 和 点1 的行号差不超过1
    规则4: r0 == r1，即 点0 和 点1 的行号相同时，必须对点1进行操作
    规则5: c0 == c1，即 点0 和 点1 的列号相同时，必须对点0进行操作
*/

int Dfs(int r0, int c0, int r1, int c1) {
  int& ans = dp[r0][c0][r1][c1];
  if (ans != -1) {
    return ans;
  }
  ans = 0;
  if (r0 == 0 || c0 == 0 || r1 == 0 || c1 == 0) {
    return ans;
  }
  if (r0 == r1 && c0 == c1) {  // 同点，答案不会变大
    ans = max(Dfs(r0, c0 - 1, r1, c1), Dfs(r0, c0, r1 - 1, c1));
  } else if (r0 == r1) {
    ans = max(Dfs(r0, c0, r1, c1 - 1), Dfs(r0, c0, r1 - 1, c1)) + g[r1][c1];
  } else if (c0 == c1) {
    ans = max(Dfs(r0 - 1, c0, r1, c1), Dfs(r0, c0 - 1, r1, c1)) + g[r0][c0];
  } else {
    int ans0 = max(Dfs(r0 - 1, c0, r1, c1), Dfs(r0, c0 - 1, r1, c1)) + g[r0][c0];
    int ans1 = max(Dfs(r0, c0, r1, c1 - 1), Dfs(r0, c0, r1 - 1, c1)) + g[r1][c1];
    ans = max(ans0, ans1);
  }
  return ans;
}

void Solver() {  //
  scanf("%d", &N);
  memset(g, 0, sizeof(g));
  int x, y, v;
  while (true) {
    scanf("%d%d%d", &x, &y, &v);
    if (x == 0 && y == 0 && v == 0) break;
    g[x][y] = v;
  }
  memset(dp, -1, sizeof(dp));
  dp[1][1][1][1] = g[0][0];
  printf("%d\n", Dfs(N, N, N, N));
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
