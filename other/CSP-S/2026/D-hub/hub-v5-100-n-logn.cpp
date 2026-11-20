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
vector<int> deg;
int leftNode = 0;  // 删除 R 层的叶子后，剩余节点数

vector<int> minLeftDis;
vector<int> splitNode;
vector<int> maxLeftToRight, maxRightToLeft;
bool CheckRange(int midCanSelectNode) {
  int midNum = splitNode.size() - 2;

  // 滑动窗口：枚举左端点，看可以覆盖的最远距离
  maxLeftToRight.clear();
  maxLeftToRight.resize(midNum + 2, 0);
  // [0, l] 都选择，最远可以覆盖的点
  int maxRight = 0;
  for (int l = 0; l <= midNum; l++) {
    while (maxRight <= midNum && minLeftDis[splitNode[maxRight]] >= maxRight - l) {
      maxRight++;
    }
    maxLeftToRight[l] = maxRight - 1;
    MyPrintf("maxLeftToRight[%d] = %d\n", l, maxRight);
  }

  maxRightToLeft.clear();
  maxRightToLeft.resize(midNum + 2, midNum + 1);
  int minLeft = midNum + 1;
  for (int r = midNum + 1; r > 0; r--) {
    while (minLeft > 0 && minLeftDis[splitNode[minLeft]] >= r - minLeft) {
      minLeft--;
    }
    maxRightToLeft[r] = minLeft + 1;
    MyPrintf("maxRightToLeft[%d] = %d\n", r, minLeft);
  }

  for (int l = 0, r = midNum + 1 - midCanSelectNode; l <= midCanSelectNode; l++, r++) {
    if (maxLeftToRight[l] + 1 >= maxRightToLeft[r]) {
      MyPrintf("maxLeftToRight[%d] = %d >= maxRightToLeft[%d] = %d\n", l, maxLeftToRight[l], r, maxRightToLeft[r]);
      return true;
    }
  }
  return false;
}

int R;
vector<vector<int>> g;
vector<int> maxDis;  // 距离叶子的最大距离
// 判断以 u 为一个端点的链，删除中间一段，是否可以满足要求
bool CheckSplit(const int L, const int pre) {
  minLeftDis.resize(n + 1, R);
  int u = L, uPre = pre;
  splitNode.clear();
  splitNode.push_back(pre);  // 左侧加一个桩
  minLeftDis[pre] = R;
  while (deg[u] == 2) {
    // 可以确保， u 的度数一定是 2，从而确保，u 是链上的一个节点
    int uMinLeftDis = R;
    int nextV = -1;
    for (auto v : g[u]) {
      if (v == uPre) continue;
      if (maxDis[v] <= R) {
        uMinLeftDis = min(uMinLeftDis, R - maxDis[v]);
      } else {
        nextV = v;
      }
    }

    splitNode.push_back(u);
    minLeftDis[u] = uMinLeftDis;
    uPre = u;
    u = nextV;
  }
  // 最后一个节点不满足度数为2，刚好作为右侧的桩
  splitNode.push_back(u);
  minLeftDis[u] = R;

  const int midNum = splitNode.size() - 2;
  const int R = u;

  // 删除中间的链，左右必选节点超过 k，不能满足要求
  const int midCanSelectNode = k - (leftNode - midNum);
  MyPrintf("CheckSplit L=%d pre=%d R=%d midNum=%d midCanSelectNode=%d\n", L, pre, R, midNum, midCanSelectNode);
  if (midCanSelectNode < 0) return false;
  return CheckRange(midCanSelectNode);
}

bool Check(const int mid) {
  R = mid;
  leftNode = n;
  for (int i = 1; i <= n; i++) {
    if (maxDis[i] <= R) {
      leftNode--;
    }
  }
  if (leftNode <= k) {
    MyPrintf("leftNode=%d <= k=%d, ok\n", leftNode, k);
    return true;  // 剪枝，一个联通分支就可以满足要求
  }
  int maxLinkRemove = leftNode - k;
  if (maxLinkRemove > 2 * R) {
    return false;  // 剪枝，链上不可能满足要求
  }

  // 重新计算每个节点的度数
  for (int u = 1; u <= n; u++) {
    deg[u] = 0;
    if (maxDis[u] <= R) continue;
    for (int v : g[u]) {
      if (maxDis[v] > R) {
        deg[u]++;
      }
    }
  }

  // 枚举判断两个联通分支是否可以满足要求
  // 显然，需要删除的点也是一个联通分支，且度数都是 2，即是一条链。
  // 对于度数为 2 的链，只能是从度数大于 2 的节点 或者度数为 0 的叶子节点开始。
  // 所有，只需要 DFS 枚举所有链，判断是否满足要求
  //   maxLeafNode 作为叶子，可以当做第一个根，来换根DP计算答案
  for (int u = 1; u <= n; u++) {
    if (deg[u] <= 0 || deg[u] == 2) continue;
    for (int v : g[u]) {
      if (deg[v] != 2) continue;  // 链上必须有节点
      if (CheckSplit(v, u)) {
        return true;
      }
    }
  }
  return false;
}

void InitDegAndMaxDis() {
  queue<int> q;
  deg.resize(n + 1, 0);
  maxDis.resize(n + 1, 0);
  for (int u = 1; u <= n; u++) {
    deg[u] = g[u].size();
    if (deg[u] == 1) {
      maxDis[u] = 1;
      MyPrintf(" maxDis[%d] = %d\n", u, maxDis[u]);
      q.push(u);
    }
  }
  while (!q.empty()) {
    const int u = q.front();
    q.pop();
    for (int v : g[u]) {
      deg[v]--;
      if (deg[v] == 1) {
        maxDis[v] = maxDis[u] + 1;
        MyPrintf(" maxDis[%d] = %d\n", v, maxDis[v]);
        q.push(v);
      }
    }
  }
}

int SearchAns() {
  if (k == n) return 0;

  InitDegAndMaxDis();

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
