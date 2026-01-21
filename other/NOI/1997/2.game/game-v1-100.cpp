/*
ID: tiankonguse
TASK: game
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "game"
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
int debug_log = 1;
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

int n, m;
vector<vector<int>> nums;
ll dp0[111][111];     // dp0[r][m] 代表前r个元素，组成m段的最大高度和
ll dp1[111][111][3];  // dp1[l][r][s] 代表区间[l,r] 组成一段，最后一个选s的高度和
ll dp2[111][111];     // dp2[l][r] 代表区间[l,r] 组成一段的最大高度和

// -1 代表没有计算， -2 代表没有答案
ll Dfs1(const int l, const int r, const int s) {
  ll& ret = dp1[l][r][s];
  if (ret != -1) return ret;

  const int sa = nums[r][s];
  const int sb = nums[r][(s + 1) % 3];
  const int sc = nums[r][(s + 2) % 3];
  ret = sc;  // 只有最后一个元素
  for (int mid = l; mid < r; mid++) {
    for (int p = 0; p < 3; p++) {
      const int pa = nums[mid][p];
      const int pb = nums[mid][(p + 1) % 3];
      const int pc = nums[mid][(p + 2) % 3];
      if ((pa >= sa && pb >= sb) || (pa >= sb && pb >= sa)) {
        ret = max(ret, Dfs1(l, mid, p) + sc);
      }
    }
  }
  return ret;
}

ll Dfs2(const int l, const int r) {
  ll& ret = dp2[l][r];
  if (ret != -1) return ret;
  ret = 0;
  for (int last = l; last <= r; last++) {
    // 中间可能都不选，选择的最后一个是 last
    for (int s = 0; s < 3; s++) {
      ret = max(ret, Dfs1(l, last, s));
    }
  }
  return ret;
}

ll Dfs0(const int r, const int k) {
  const int rn = r + 1;
  if (r < 0 || k <= 0 || k > rn) return -2;
  ll& ret = dp0[r][k];
  if (ret != -1) return ret;
  ret = -2;
  if (k == 1) {
    ret = Dfs2(0, r);
  } else {
    for (int l = 0; l < r; l++) {
      // [l+1, r] 组成一段，[0, l] 组成 k-1 段
      const ll tmp0 = Dfs0(l, k - 1);
      const ll tmp1 = Dfs2(l + 1, r);
      if (tmp0 != -2 && tmp1 != -2) {
        ret = max(ret, tmp0 + tmp1);
      }
    }
  }

  return ret;
}

void Solver() {  //
  scanf("%d%d", &n, &m);
  nums.resize(n, vector<int>(3, 0));
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &nums[i][0], &nums[i][1], &nums[i][2]);
  }
  memset(dp0, -1, sizeof(dp0));  // 代表没有计算答案
  memset(dp1, -1, sizeof(dp1));  // 代表没有计算答案
  memset(dp2, -1, sizeof(dp2));  // 代表没有计算答案
  printf("%lld\n", Dfs0(n - 1, m));
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
