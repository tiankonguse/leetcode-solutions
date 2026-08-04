/*
ID: tiankonguse
TASK: InfectiousDiseaseControl
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1041
PATH:
submission:
*/
#define TASK "InfectiousDiseaseControl"
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

int n, p;
vector<vector<int>> g;
vector<vector<int>> G;
vector<int> childNum;
vector<int> level;
vector<int> que;

void DfsLevel(int u, int pre) {
  childNum[u] = 1;
  for (int v : g[u]) {
    if (v == pre) continue;
    G[u].push_back(v);
    level[v] = level[u] + 1;
    DfsLevel(v, u);
    childNum[u] += childNum[v];
  }
}
int ans = 0;
void UpdateAns(int preDelNum) {
  ans = min(ans, n - preDelNum);  // 更新答案
}

void Dfs(const int l, const int r, const int preDelNum) {
  if (l == r) {
    UpdateAns(preDelNum);
    // MyPrintf("l = %d, r = %d, preLev = %d, preDelNum = %d\n", l, r, preLev, preDelNum);
    // for (int i = 0; i < r; i++) {
    //   MyPrintf("%d ", que[i]);
    // }
    // MyPrintf("\n");
    return;
  }
  //   MyPrintf("l = %d, r = %d, preLev = %d, preDelNum = %d\n", l, r, preLev, preDelNum);
  //   for (int i = l; i < r; i++) {
  //     MyPrintf("%d ", i);
  //   }
  //   MyPrintf("\n");
  for (int i = l; i < r; i++) {  // [l, r)
    // 枚举删除节点 i 与父节点的边
    // MyPrintf("del = %d\n", que[i]);
    int p = r;
    for (int j = l; j < r; j++) {
      if (i == j) continue;
      for (auto v : G[que[j]]) {
        que[p] = v;
        p++;
      }
    }
    Dfs(r, p, preDelNum + childNum[que[i]]);
  }
}

void Solver() {  //
  scanf("%d%d", &n, &p);
  if (p + 1 != n) {
    printf("0\n");
    return;
  }
  g.resize(n);
  for (int i = 0; i < p; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  G.resize(n);
  level.resize(n, 0);
  childNum.resize(n, 0);
  DfsLevel(0, -1);
  que.resize(n);

  ans = n;
  que[0] = 0;
  int p = 1;
  for (int v : G[0]) {
    que[p] = v;
    p++;
  }
  Dfs(1, p, 0);
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
