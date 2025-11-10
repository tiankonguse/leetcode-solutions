/*
ID: tiankonguse
TASK: banquet
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "banquet"
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
#define TASKNO 1
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

int T;
int n;
vector<pair<double, double>> nums;  // (pos, time)
vector<double> preMin;
vector<double> sufMax;
void Solver() {  //
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    nums.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      scanf("%lf", &nums[i].first);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%lf", &nums[i].second);
    }
    sort(nums.begin() + 1, nums.begin() + 1 + n);
    preMin.resize(n + 2);
    sufMax.resize(n + 2);
    preMin[0] = INT64_MAX;
    for (int i = 1; i <= n; i++) {
      preMin[i] = min(preMin[i - 1], nums[i].first - nums[i].second);
    }
    sufMax[n + 1] = INT64_MIN;
    for (int i = n; i >= 1; i--) {
      sufMax[i] = max(sufMax[i + 1], nums[i].first + nums[i].second);
    }
    double ansTime = max(nums[1].second, sufMax[1] - nums[1].first);  // 在第一个点处设置目标点
    double ansPos = nums[1].first;
    MyPrintf("first Ans: pos=%.2lf, time=%.2lf\n", ansPos, ansTime);
    auto UpdateAns = [&](double tmpPos, double tmpTime) {
      MyPrintf("  try pos=%.2lf, time=%.2lf\n", tmpPos, tmpTime);
      if (tmpTime < ansTime) {
        ansTime = tmpTime;
        ansPos = tmpPos;
        MyPrintf("  update ans to pos=%.2lf, time=%.2lf\n", ansPos, ansTime);
      }
    };
    for (int i = 1; i < n; i++) {
      // 目标点设置在 (i, i+1] 区间内
      double lv = nums[i].first;
      double rv = nums[i + 1].first;
      double leftMin = preMin[i];
      double rightMax = sufMax[i + 1];
      double mid = (rightMax + leftMin) / 2;
      MyPrintf("i=%d, leftMin=%.2lf, rightMax=%.2lf, mid=%.2lf lv=%.2lf rv=%.2lf\n", i, leftMin, rightMax, mid, lv, rv);
      if (mid <= lv) {  // 选择 left 最优
        double tmpPos = lv;
        double tmpTime = max(lv - leftMin, rightMax - lv);
        UpdateAns(tmpPos, tmpTime);
      } else if (mid >= rv) {
        double tmpPos = rv;
        double tmpTime = max(rv - leftMin, rightMax - rv);
        UpdateAns(tmpPos, tmpTime);
      } else {
        double tmpPos = mid;
        double tmpTime = max(mid - leftMin, rightMax - mid);
        UpdateAns(tmpPos, tmpTime);
      }
    }
    MyPrintf("Final Ans: pos=%.2lf, time=%.2lf\n", ansPos, ansTime);
    ll ans = ansPos * 2;
    if (ans % 2 == 1) {
      printf("%lld.5\n", ans / 2);
    } else {
      printf("%lld\n", ans / 2);
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
