/*
ID: tiankonguse
TASK: traverse
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "traverse"
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
#define USACO_TASK_FILE 1
#define TASKNO 13
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

int n, k;
struct Edge {
  int to;
  int idx;
  int specialNum;
  Edge() : to(0), idx(0), specialNum(0) {}
  Edge(int to, int idx) : to(to), idx(idx), specialNum(0) {}
};
vector<vector<Edge>> g;
// vector<pair<int, int>> edges;
unordered_set<int> specialEdges;
vector<int> childTreeSpecialCount;  // 子树中特殊边数量
vector<ll> factorials;

int DfsChild(const int u, const int p) {
  int childTreeSpecialNum = 0;
  for (auto& e : g[u]) {
    if (e.to == p) continue;
    e.specialNum = DfsChild(e.to, u);  // 子树中特殊边数量
    if (specialEdges.count(e.idx)) {
      e.specialNum++;  // 子边的特殊边数量
    }
    MyPrintf("u=%d e.to=%d e.specialNum=%d\n", u, e.to, e.specialNum);
    childTreeSpecialNum += e.specialNum;
  }
  MyPrintf("u=%d childTreeSpecialNum=%d\n", u, childTreeSpecialNum);
  return childTreeSpecialCount[u] = childTreeSpecialNum;  // 子树中特殊边数量
}

void DfsParent(int u, int p, int idx, int parentSpecial) {
  MyPrintf("u=%d p=%d idx=%d parentSpecial=%d\n", u, p, idx, parentSpecial);
  int isSpecial = childTreeSpecialCount[u] + parentSpecial;
  assert(isSpecial == k);
  for (auto& e : g[u]) {
    if (e.to == p) {  // 父节点
      e.specialNum = parentSpecial;
      continue;
    }
    int withoutChild = k - e.specialNum;
    if (specialEdges.count(e.idx)) {
      withoutChild++;  // e.specialNum 包含的边被删除，加回来
    }
    MyPrintf("u=%d e.to=%d e.idx=%d e.specialNum=%d withoutChild=%d\n", u, e.to, e.idx, e.specialNum, withoutChild);
    DfsParent(e.to, u, e.idx, withoutChild);
  }
}

ll DfsAns(int u, int p) {
  ll res = 1;

  for (auto& e : g[u]) {
    if (e.to == p) continue;
    res = (res * DfsAns(e.to, u)) % mod;
  }

  ll childNum = g[u].size();
  ll specialChildNum = 0;
  for (auto& e : g[u]) {
    if (e.specialNum > 0) {
      specialChildNum++;
    }
  }
  ll nowRes = 0;
  ll nonSpecialChildNum = childNum - specialChildNum;
  if (childNum > 2) {
    // 两个端点分别选择一个特殊变和非特殊边，中间的任意排列组合
    if (nonSpecialChildNum > 0) {
      // C(specialNum, 1) * C(nonSpecialNum, 1) * (childNum -2)!
      ll add = (specialChildNum * nonSpecialChildNum) % mod;
      add = (add * factorials[childNum - 2]) % mod;
      nowRes = (nowRes + add) % mod;
    }
    // 选择两个特殊边作为端点，中间的任意排列组合
    if (specialChildNum >= 2) {
      // C(specialNum, 2) * (childNum -2)!
      ll add = (specialChildNum * (specialChildNum - 1) / 2) % mod;
      add = (add * factorials[childNum - 2]) % mod;
      nowRes = (nowRes + add) % mod;
    }
  }else{
    nowRes = 1;
  }
  return res * nowRes % mod;
}

void InitIO() {
  scanf("%d%d", &n, &k);
  g.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    g[i].clear();
  }
  // edges.resize(n + 1);
  for (int idx = 1; idx < n; idx++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(Edge(v, idx));
    g[v].push_back(Edge(u, idx));
    // edges[idx] = {u, v};
  }
  specialEdges.clear();
  for (int i = 0; i < k; i++) {
    int idx;
    scanf("%d", &idx);
    specialEdges.insert(idx);
  }
  childTreeSpecialCount.clear();
  childTreeSpecialCount.resize(n + 1, 0);
}
void Solver(int) {  //
  InitIO();
  factorials.resize(n + 1);
  factorials[0] = 1;
  for (int i = 1; i <= n; i++) {
    factorials[i] = (factorials[i - 1] * i) % mod;
  }
  DfsChild(1, 0);
  DfsParent(1, 0, 0, 0);
  printf("%lld\n", DfsAns(1, 0));
}
void Solver() {  //
  int C, T;
  scanf("%d%d", &C, &T);
  while (T--) {
    Solver(T);
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
