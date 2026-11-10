/*
ID: tiankonguse
TASK: hub
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17834
PATH: P17834 [CSP-S 2026] 研发基地 / hub
submission:
*/
#define TASK "hub"
#define TASKEX "-tmp"

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
int output_ans = 1;
int debug_assert = 0;
#define MyPrintf(...)                                 \
  do {                                                \
    if (debug_log || output_ans) printf(__VA_ARGS__); \
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
#define LOCAL_IO 5  // 本地跑测试样例
#define MAX_TIME 2000
#ifdef LOCAL_IO
// #define TASKNO 6    // 只跑指定组的测试用例
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

int c, t, n, k;
vector<vector<int>> G;
vector<int> deg;
int leftNode = 0;  // 删除 R 层的叶子后，剩余节点数
// int R;
vector<int> maxDis;  // 距离叶子的最大距离

int maxleafDepth = -1;
int maxLeafNode = -1;
bool DfsRemoveLeaf(const int u, const int pre, const int depth) {
  for (int l = 0; l < G[u].size(); l++) {
    const int childNum = G[u].size();
    const int v = G[u][l];
    if (v == pre) continue;
    if (DfsRemoveLeaf(v, u, depth + 1)) {  // 儿子被删除了
      swap(G[u][l], G[u][childNum - 1]);
      G[u].pop_back();
      l--;
      deg[u]--;

      // 儿子删除，更新父节点的最大距离
      maxDis[u] = min(maxDis[u], maxDis[v] - 1);
    }
  }
  if (pre != -1 && deg[u] == 1 && maxDis[u] > 0) {
    MyPrintf("remove leaf: u=%d deg=%d maxDis=%d depth=%d\n", u, deg[u], maxDis[u], depth);
    G[u].pop_back();  // 断开与父节点的连接
    deg[u]--;         // 更新自己的度数， 父节点的信息由父节点自己更新
    leftNode--;
    return true;
  }

  MyPrintf("u=%d deg=%d maxDis=%d depth=%d\n", u, deg[u], maxDis[u], depth);
  // 没有删除的儿子，记录最深的那个叶子
  if (depth > maxleafDepth) {
    maxleafDepth = depth;
    maxLeafNode = u;
  }
  return false;
}

bool IsSplit(int u) {
  return deg[u] == 1 || deg[u] > 2;  //
}

vector<int> splitNode;

bool CheckRange(int midCanSelectNode) {
  int midNum = splitNode.size() - 2;
  // 枚举左边选择的个数
  for (int leftSelect = 0; leftSelect <= midCanSelectNode; leftSelect++) {
    const int rightSelect = midCanSelectNode - leftSelect;
    const int leftPos = leftSelect + 1;
    const int rightPos = midNum - rightSelect;
    // [leftPos, rightPos] 区间都没被选择
    bool ok = true;
    for (int i = leftPos; i <= rightPos; i++) {
      const int v = splitNode[i];
      const int leftDis = i - leftPos + 1;
      const int rightDis = rightPos - i + 1;
      const int minDis = min(leftDis, rightDis);
      if (minDis > maxDis[v]) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return true;
    }
  }
  return false;
}

// 判断以 u 为一个端点的链，删除中间一段，是否可以满足要求
bool CheckSplit(const int L, const int pre) {
  splitNode.clear();
  int u = L, uPre = pre;
  splitNode.push_back(pre);  // 左侧加一个桩
  splitNode.push_back(u);
  while (!IsSplit(u)) {
    // 可以确保， u 的度数一定是 2，从而确保，u 是链上的一个节点
    for (auto v : G[u]) {
      if (v == uPre) continue;
      splitNode.push_back(v);
      uPre = u;
      u = v;
      break;
    }
  }
  // 最后一个节点不满足度数为2，刚好作为右侧的桩
  // splitNode.pop_back();

  const int midNum = splitNode.size() - 2;
  const int R = u;

  // 删除中间的链，左右必选节点超过 k，不能满足要求
  const int midCanSelectNode = k - (leftNode - midNum);
  MyPrintf("CheckSplit L=%d pre=%d R=%d midNum=%d midCanSelectNode=%d\n", L, pre, R, midNum, midCanSelectNode);
  if (midCanSelectNode < 0) return false;
  return CheckRange(midCanSelectNode);
}

bool DfsRemoveLink(int u, int pre) {
  for (auto v : G[u]) {
    if (v == pre) continue;
    if (IsSplit(u) && !IsSplit(v) && CheckSplit(v, u)) {
      return true;
    }
    if (DfsRemoveLink(v, u)) {
      return true;
    }
  }
  return false;
}

vector<vector<int>> g;
bool Check(const int R) {
  deg.clear();
  deg.resize(n + 1, 0);
  G = g;
  for (int i = 1; i <= n; i++) {
    deg[i] = G[i].size();
  }
  maxDis.clear();
  maxDis.resize(n + 1, R);
  leftNode = n;
  MyPrintf("root=%d\n", 1);
  maxleafDepth = -1;
  maxLeafNode = -1;
  DfsRemoveLeaf(1, -1, 0);
  if (leftNode <= k) {
    MyPrintf("leftNode=%d <= k=%d, ok\n", leftNode, k);
    return true;  // 剪枝，一个联通分支就可以满足要求
  }
  // 0 这个根节点是随机选择的，有可能也在最后 R 层，需要删除
  // 最简单的思路是再换一个根节点，重新跑 DfsRemoveLeaf
  // 除了 0 节点，其他节点都完成缩点，所以应该选择离 0 最远的叶子节点作为根节点
  const int tmpRoot = maxLeafNode;
  MyPrintf("root=%d\n", tmpRoot);
  DfsRemoveLeaf(tmpRoot, -1, 0);
  if (leftNode <= k) {
    MyPrintf("leftNode=%d <= k=%d, ok\n", leftNode, k);
    return true;  // 一个联通分支就可以满足要求
  }
  // 枚举判断两个联通分支是否可以满足要求
  // 显然，需要删除的点也是一个联通分支，且度数都是 2，即是一条链。
  // 对于度数为 2 的链，只能是从度数大于 2 的节点 或者度数为 0 的叶子节点开始。
  // 所有，只需要 DFS 枚举所有链，判断是否满足要求
  //   maxLeafNode 作为叶子，可以当做第一个根，来换根DP计算答案
  MyPrintf("DfsRemoveLink root=%d\n", tmpRoot);
  return DfsRemoveLink(tmpRoot, -1);
}

int SearchAns() {
  if (k == n) return 0;
  int l = 1, r = n;  // [l, r)
  while (l < r) {
    int mid = (l + r) / 2;
    MyPrintf("mid=%d\n", mid);
    int ok = Check(mid);
    MyPrintf("l=%d r=%d mid=%d ok=%d\n", l, r, mid, ok);
    if (ok) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return r;
}

void Solver() {  //
  scanf("%d%d", &c, &t);
  while (t--) {
    g.clear();
    scanf("%d%d", &n, &k);
    g.resize(n + 1);
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      // u--, v--;  // 1-based -> 0-based
      g[u].push_back(v);
      g[v].push_back(u);
    }
    printf("%d\n", SearchAns());
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
#ifndef LOCAL_IO
  MyPrintf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef LOCAL_IO
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
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, LOCAL_IO, AC * (100 / LOCAL_IO));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef LOCAL_IO
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= LOCAL_IO; i++) {
    fileIndex = i;
    output_ans = 0;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef LOCAL_IO
    fclose(stdout);
    output_ans = 1;
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  output_ans = 1;
  DiffSummary(stdout_fd);
#endif
  return 0;
}
