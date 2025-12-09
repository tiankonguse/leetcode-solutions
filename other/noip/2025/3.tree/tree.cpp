/*
ID: tiankonguse
TASK: tree
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "tree"
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
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 2
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

int n, m;
vector<vector<int>> g;
vector<vector<vector<pair<ll, bool>>>> dp;  // dp[u][maxMex][left] 的最大价值，以及是否能构造出
vector<vector<pair<ll, bool>>> dp2;  // dp[u][left] 的最大价值，以及是否能构造出
vector<ll> childSize;
void Init(int n) {  //
  childSize.clear();
  childSize.resize(n + 1, 0);
  dp.clear();
  dp.resize(n + 1, vector<vector<pair<ll, bool>>>(n + 1, vector<pair<ll, bool>>(n + 1, {-1, false})));
}

ll InitChildSize(int u) {
  ll& ret = childSize[u];
  ret = 1;
  for (int v : g[u]) {
    ret += InitChildSize(v);
  }
  return ret;
}

pair<ll, bool> Dfs(const int u, const int uMex, const int left) {  //
  auto& [uAns, uHas] = dp[u][uMex][left];
  if (uAns != -1) {
    return {uAns, uHas};
  }
  uAns = 0;
  uHas = false;

  // 第一种， dp[u][uMex-1][left+1] 存在答案，则消耗一个空闲节点，使得 mex 增加 1
  if (uMex > 0 && left < n) {
    auto [vSum, vHas] = Dfs(u, uMex - 1, left + 1);
    if (vHas) {  // 空闲节点取值 uMex - 2， 当前根取值 uMex - 1，从而得到 uMex
      uAns = vSum + uMex;
      uHas = true;
    }
  }
  for (int v : g[u]) {  // 某个儿子的 vMex 为 uMex-1, 其他儿子对 vMex 无限制，但需要保障总空闲节点个数为 left,且价值最大
    for(int )
  }
  return {uAns, uHas};
}
void Solver() {  //
  ll t;
  scanf("%lld", &t);
  g.clear();
  while (t--) {
    scanf("%d%d", &n, &m);
    g.resize(n + 1);
    for (int i = 2; i <= n; i++) {
      int p;
      scanf("%d", &p);
      g[p].push_back(i);
    }
    Init(n);
    InitChildSize(1);
    ll ans = 0;
    for (int maxMex = 0; maxMex <= n; maxMex++) {
      auto [vSum, hasMex] = Dfs(1, maxMex, 0);
      if (hasMex) {
        ans = max(ans, vSum);
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
