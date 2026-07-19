/*
ID: tiankonguse
TASK: rectangle-covering
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "rectangle-covering"
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

struct Rectangle {
  int top, bottom, left, right;
  int num;
  Rectangle() : num(0) {}
  void Add(pair<int, int> p) {
    auto [x, y] = p;
    if (num == 0) {
      top = bottom = y;
      left = right = x;
      num = 1;
      return;
    }
    top = max(top, y);
    bottom = min(bottom, y);
    left = min(left, x);
    right = max(right, x);
    num++;
  }
};
vector<Rectangle> rs;

int n, k;
vector<pair<int, int>> points;

int ans;
void UpdateAns() {  //
  int tmpAns = 0;
  for (int i = 0; i < k; i++) {
    if (rs[i].num == 0) continue;
    tmpAns += (rs[i].top - rs[i].bottom) * (rs[i].right - rs[i].left);
  }
  ans = min(ans, tmpAns);
}

bool OverlapIn(int x, int y, int j) {
  return x >= rs[j].bottom && x <= rs[j].top && y >= rs[j].left && y <= rs[j].right;
}

// 判断 i 的其中一个点是否在 j 中
bool OverlapIn(int i, int j) {
  if (OverlapIn(rs[i].bottom, rs[i].left, j)) return true;
  if (OverlapIn(rs[i].bottom, rs[i].right, j)) return true;
  if (OverlapIn(rs[i].top, rs[i].left, j)) return true;
  if (OverlapIn(rs[i].top, rs[i].right, j)) return true;
  return false;
}

// 检查第 i 个矩阵与其他矩阵是否有交集
bool Overlap(int i) {
  for (int j = 0; j < k; j++) {
    if (i == j) continue;
    if (rs[j].num == 0) continue;
    if (OverlapIn(i, j) || OverlapIn(j, i)) return true;
  }
  return false;
}
void Dfs(int p) {
  if (p == n) {
    UpdateAns();
    return;
  }
  // 枚举第 p 个点加入的矩阵
  for (int i = 0; i < k; i++) {
    const Rectangle back = rs[i];
    rs[i].Add(points[p]);
    if (!Overlap(i)) {
      Dfs(p + 1);
    }
    rs[i] = back;
  }
}

void Solver() {  //
  scanf("%d%d", &n, &k);
  points.resize(n);
  rs.resize(k);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &points[i].first, &points[i].second);
  }
  ans = 1000 * 1000;
  Dfs(0);

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
