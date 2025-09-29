/*
ID: tiankonguse
TASK: brackets
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P5658
PATH:  P5658 [CSP-S2019] 括号树
submission:
*/
#define TASK "brackets"
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
#ifdef USACO_LOCAL_JUDGE
// #define USACO_TASK_FILE 20
#define TASKNO 20
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
}

const int N = 5e5 + 10;
int n;
char values[N];
ll dp[N];
int fa[N];
vector<vector<int>> g;

ll ans = 0;

vector<int> mySta;
void Dfs(const int u, const ll preSum, const int depth) {
  const int staSize = mySta.size();
  if (staSize > 0 && values[u] == ')' && values[mySta.back()] == '(') {
    const int leftPos = mySta.back();
    dp[u] = dp[fa[leftPos]] + 1;
    mySta.pop_back();
    for (auto v : g[u]) {
      Dfs(v, preSum + dp[u], depth + 1);
    }
    mySta.push_back(leftPos);
  } else {
    dp[u] = 0;
    mySta.push_back(u);
    for (auto v : g[u]) {
      Dfs(v, preSum + dp[u], depth + 1);
    }
    mySta.pop_back();
  }
  //   MyPrintf("u=%d, dp=%lld\n", u, dp[u]);
  ans ^= u * (preSum + dp[u]);
}

void Solver() {  //
  scanf("%d", &n);
  values[0] = ' ';
  scanf("%s", values + 1);
  g.clear();
  g.resize(n + 1);
  fa[1] = 0;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i]);
    g[fa[i]].push_back(i);
  }
  mySta.clear();
  mySta.reserve(n + 1);
  ans = 0;
  dp[0] = 0;
  Dfs(1, 0, 0);
  printf("%lld\n", ans);
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
