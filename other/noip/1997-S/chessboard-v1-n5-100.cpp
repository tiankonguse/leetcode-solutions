/*
ID: tiankonguse
TASK: chessboard
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "chessboard"
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

// 判断一个数是否为质数
// 时间复杂度 O(sqrt(n))
bool IsPrime2(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return n >= 2;  // 1 不是质数, 2和3是质数
}

vector<int> isPrm;
vector<vector<int>> edges;
void Init(int n) {
  isPrm.resize(100, 0);
  for (int i = 2; i < 100; i++) {
    if (IsPrime2(i)) {
      isPrm[i] = 1;
    }
  }
  int nn = n * n;
  edges.resize(nn + 1);
  for (int i = 1; i <= nn; i++) {
    MyPrintf("%d: ", i);
    for (int j = 1; j <= nn; j++) {
      if (i == j) continue;
      if (isPrm[i + j]) {
        edges[i].push_back(j);
        MyPrintf("%d ", j);
      }
    }
    MyPrintf("\n");
  }
}

vector<vector<int>> g;
vector<vector<int>> ans;
vector<int> flag;
int ansSum = 0;
int n;
void UpdateAns() {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += g[i][0];
    sum += g[0][i];
  }
  sum -= g[0][0];
  if (sum < ansSum) {
    ans = g;
    ansSum = sum;
  }
}
void Dfs(const int x, const int y) {
  if (y == n) {
    Dfs(x + 1, 0);
    return;
  }
  if (x == n) {
    UpdateAns();
    return;
  }
  // 根据上个位置，枚举当前位置的值
  int preVal = x > 0 ? g[x - 1][y] : g[x][y - 1];
  for (auto val : edges[preVal]) {
    if (flag[val]) continue;                              // 已经使用过
    if (x > 0 && !isPrm[g[x - 1][y] + val]) continue;  // 上个位置和当前位置不相邻
    if (y > 0 && !isPrm[g[x][y - 1] + val]) continue;  // 左个位置和当前位置不相邻
    g[x][y] = val;
    flag[val] = 1;
    Dfs(x, y + 1);
    flag[val] = 0;
  }
}
void Solver() {  //
  scanf("%d", &n);
  Init(n);
  ans.resize(n, vector<int>(n, n * n));
  ansSum = INT_MAX;
  g.resize(n, vector<int>(n));
  flag.resize(n * n + 1, 0);
  g[0][0] = 1;
  flag[1] = 1;
  if (n == 1) {
    printf("NO\n");
  } else {
    Dfs(0, 1);
    if (ansSum < INT_MAX) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          printf("%d ", ans[i][j]);
        }
        printf("\n");
      }
    } else {
      printf("NO\n");
    }
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
