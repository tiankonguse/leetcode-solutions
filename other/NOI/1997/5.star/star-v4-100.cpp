/*
ID: tiankonguse
TASK: star
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "star"
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

int n;
vector<tuple<int, int, int, int>> nums;
unordered_set<ll> H;
vector<int> X, Y, Z;
int flag[222][222][222];
void Solver() {  //
  scanf("%d", &n);

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int x, y, z, r;
    scanf("%d%d%d%d", &x, &y, &z, &r);
    x += 1200 - r;
    y += 1200 - r;
    z += 1200 - r;
    r *= 2;
    X.push_back(x);
    X.push_back(x + r);
    Y.push_back(y);
    Y.push_back(y + r);
    Z.push_back(z);
    Z.push_back(z + r);
    nums.push_back(make_tuple(x, y, z, r));
  }
  sort(X.begin(), X.end());
  sort(Y.begin(), Y.end());
  sort(Z.begin(), Z.end());
  X.erase(unique(X.begin(), X.end()), X.end());
  Y.erase(unique(Y.begin(), Y.end()), Y.end());
  Z.erase(unique(Z.begin(), Z.end()), Z.end());
  for (auto [x, y, z, r] : nums) {
    const auto xit = lower_bound(X.begin(), X.end(), x);
    const auto yit = lower_bound(Y.begin(), Y.end(), y);
    const auto zit = lower_bound(Z.begin(), Z.end(), z);
    // 左下角为 (x,y,z) 边长为 r 的正方体被三个平面列表 X, Y, Z 切割为若干个长方体 (x,y,z, xr, yr, zr)
    for (auto itX = xit; *itX < x + r; itX++) {
      for (auto itY = yit; *itY < y + r; itY++) {
        for (auto itZ = zit; *itZ < z + r; itZ++) {
            int offsetX = itX - X.begin();
            int offsetY = itY - Y.begin();
            int offsetZ = itZ - Z.begin();
            if (flag[offsetX][offsetY][offsetZ]) {
                continue;
            }
            flag[offsetX][offsetY][offsetZ] = 1;
            int xr = *next(itX) - *itX;
            int yr = *next(itY) - *itY;
            int zr = *next(itZ) - *itZ;
            ans += xr * yr * zr;
        }
      }
    }
  }
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
