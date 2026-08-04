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
struct Node {
  int u;
  int preBrother, nextBrother;
  int leftChild, rightChild;
  Node(int u = 0) : u(u) {
    preBrother = nextBrother = -1;
    leftChild = rightChild = -1;
  }
};
vector<Node> que;

void DfsLevel(int u, int preBrother) {
  childNum[u] = 1;
  for (int v : g[u]) {
    if (v == preBrother) continue;
    G[u].push_back(v);
    level[v] = level[u] + 1;
    DfsLevel(v, u);
    childNum[u] += childNum[v];
  }
  // 儿子节点按子树大小降序排列，方便后续枚举删除节点时，优先删除子树大的节点
  sort(G[u].begin(), G[u].end(), [&](int a, int b) { return childNum[a] > childNum[b]; });
}
int ans = 0;
void UpdateAns(int preDelNum) {
  ans = min(ans, n - preDelNum);  // 更新答案
}

void Dfs(const int l, const int r, const int preDelNum, const int forestNum) {
  if (l == -1 || l == r) {
    UpdateAns(preDelNum);
    return;
  }
  // 森林都删除依旧比当前答案大，则不需要继续枚举删除节点
  if (n - (preDelNum + forestNum) >= ans) return;

  int len = 0;

  int p = r;
  int preOffset = 0;
  que[0] = Node(0);                                   // 使用 节点 0 当做 head
  for (int i = l; i != -1; i = que[i].nextBrother) {  // [l, r)
    len++;
    for (auto v : G[que[i].u]) {
      que[p] = Node(v);
      que[preOffset].nextBrother = p;
      que[p].preBrother = preOffset;
      preOffset = p;
      if (que[i].leftChild == -1) que[i].leftChild = p;
      que[i].rightChild = p;
      p++;
    }
  }
  for (int i = l; i != -1; i = que[i].nextBrother) {
    const int u = que[i].u;
    // 枚举删除节点 i 及其子树
    if (childNum[u] == 1) {  // 说明没有儿子，不影响儿子节点
      Dfs(que[0].nextBrother, p, preDelNum + childNum[u], forestNum - childNum[u] - len + 1);
      continue;
    }

    const int leftChild = que[i].leftChild;
    const int rightChild = que[i].rightChild;
    if (que[leftChild].preBrother != -1) que[que[leftChild].preBrother].nextBrother = que[rightChild].nextBrother;
    if (que[rightChild].nextBrother != -1) que[que[rightChild].nextBrother].preBrother = que[leftChild].preBrother;
    Dfs(que[0].nextBrother, p, preDelNum + childNum[que[i].u], forestNum - childNum[que[i].u] - len + 1);
    if (que[leftChild].preBrother != -1) que[que[leftChild].preBrother].nextBrother = leftChild;
    if (que[rightChild].nextBrother != -1) que[que[rightChild].nextBrother].preBrother = rightChild;
  }
}

void Solver() {  //
  scanf("%d%d", &n, &p);
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
  que[0] = Node(0);
  int p = 1;
  int preOffset = -1;
  for (int v : G[0]) {
    que[p] = Node(v);
    if (preOffset != -1) {
      que[preOffset].nextBrother = p;
      que[p].preBrother = preOffset;
    }
    preOffset = p;
    p++;
  }
  Dfs(1, p, 0, n - 1);
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
