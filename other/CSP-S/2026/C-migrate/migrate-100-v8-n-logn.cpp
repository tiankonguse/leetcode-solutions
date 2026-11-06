/*
ID: tiankonguse
TASK: migrate
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17833?contestId=369912
PATH: P17833 [CSP-S 2026] 迁徙 / migrate
submission:
*/
#define TASK "migrate"
#define TASKEX "-100-v9"

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
int output_ans = 0;
int debug_assert = 0;
#define MyPrintf(...)                                  \
  do {                                                 \
    if (debug_log && !output_ans) printf(__VA_ARGS__); \
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
#define LOCAL_IO 1            // 本地跑测试样例
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 6
// #define TASKNO 6
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

ll c, t;
ll n, d;
vector<ll> nums;

ll SolverDp() {
  if (n < 4 || d == 1) return 0;
  // dpRightMost[i] 右侧作为最右的答案
  vector<ll> dpRightMost(n, 0);  // dpRightMost[i] i 作为倒数第二条，下一跳的方案数
  vector<ll> dpRightSum(n, 0);   // dpRightSum[i] i 下一跳作为倒数第二条 或者 作为中间的答案的方案数
  for (int R = n - 2; R > 0; R--) {
    // 找到  [nums[R],nums[R] + d] 内存在的最大值位置
    int RRightMax = upper_bound(nums.begin() + R, nums.end(), nums[R] + d) - nums.begin() - 1;
    if (RRightMax == R) {  // 说明 D 步内不可达
      MyPrintf("R=%d skip 1\n", R);
      continue;
    }
    const int L = R - 1;
    if (nums[L] + d >= nums[RRightMax]) {
      MyPrintf("R=%d skip 2\n", R);
      continue;  // 不存在下一跳
    }

    // 找到大于 nums[L] + d 的最小值位置
    int LRightMin = upper_bound(nums.begin() + L, nums.end(), nums[L] + d) - nums.begin();
    LRightMin = max(LRightMin, R + 1);  // 有可能左边很远，需要保证在 R 右侧
    if (LRightMin <= RRightMax) {
      dpRightMost[R] += RRightMax - LRightMin + 1;
    }
    MyPrintf("one dpRightMost[%d] = %lld, LRightMin=%d RRightMax=%d\n", R, dpRightMost[R], LRightMin, RRightMax);

    // RRightMax 回跳，如果只能覆盖 R，不能覆盖 RLeft，则 R 可以作为中间的答案
    dpRightSum[R] = dpRightMost[R] + dpRightSum[RRightMax];
    MyPrintf("sum dpRightSum[%d] = %lld\n", R, dpRightSum[R]);
  }

  vector<ll> dpLeftMost(n, 0);  // dpLeftMost[i] i 作为倒数第二条，上一跳的方案数
  vector<ll> dpLeftSum(n, 0);   // dpLeftSum[i] i 上一跳作为倒数第二条 或者 作为中间的答案的方案数
  for (int L = 1; L < n - 1; L++) {
    // 找到  [nums[L]-d ,nums[L]] 内存在的最小值位置
    int LLeftMin = lower_bound(nums.begin(), nums.end(), nums[L] - d) - nums.begin();
    if (LLeftMin == L) {  // 说明 D 步内不可达
      MyPrintf("L=%d skip `\n", L);
      continue;
    }

    const int R = L + 1;
    if (nums[R] - d <= nums[LLeftMin]) {
      MyPrintf("L=%d skip 2\n", L);
      continue;  // 不存在上一跳
    }
    // 找到大于 [nums[R] - d , nums[R]] 的最小值位置
    int RLeftMin = lower_bound(nums.begin(), nums.end(), nums[R] - d) - nums.begin();
    RLeftMin--;                       // 不能覆盖 nums[LRight] - d
    RLeftMin = min(RLeftMin, L - 1);  // 有可能右边很远，需要保证在 L 左侧
    if (LLeftMin <= RLeftMin) {
      dpLeftMost[L] += RLeftMin - LLeftMin + 1;
    }
    MyPrintf("one dpLeftMost[%d] = %lld, LLeftMin=%d RLeftMin=%d\n", L, dpLeftMost[L], LLeftMin, RLeftMin);

    // LLeftMin 回跳，如果只能覆盖 L，不能覆盖 LRight，则 L 可以作为中间的答案
    dpLeftSum[L] = dpLeftMost[L] + dpLeftSum[LLeftMin];
    MyPrintf("sum dpLeftSum[%d] = %lld\n", L, dpLeftSum[L]);
  }

  // ll ans = 0;
  ll ans = 0;
  for (int L = 1, R = 2; R + 1 < n; L++, R++) {
    int LRightMax = upper_bound(nums.begin() + L, nums.end(), nums[L] + d) - nums.begin() - 1;
    int RRightMax = upper_bound(nums.begin() + R, nums.end(), nums[R] + d) - nums.begin() - 1;
    if (LRightMax <= R || nums[LRightMax] - d <= nums[L - 1]) {  // L 右侧至少覆盖两个点，才能形成2条路径
      MyPrintf("LRightMax=%d <= R=%d skip\n", LRightMax, R);
      continue;
    }
    int RLeftMin = lower_bound(nums.begin(), nums.end(), nums[R] - d) - nums.begin();
    int LLeftMin = lower_bound(nums.begin(), nums.end(), nums[L] - d) - nums.begin();
    if (RLeftMin >= L || nums[RLeftMin] + d >= nums[R + 1]) {  // R 左侧至少覆盖两个点，才能形成2条路径
      MyPrintf("RLeftMin=%d >= L=%d skip\n", RLeftMin, L);
      continue;
    }

    ll leftSum = dpLeftMost[R];
    MyPrintf("LLeftMin=%d RLeftMin=%d leftSum=%lld\n", LLeftMin, RLeftMin, leftSum);
    if (LLeftMin == RLeftMin) {
      leftSum += dpLeftSum[LLeftMin];
    }
    ll rightSum = dpRightMost[L];
    MyPrintf("LRightMax=%d RRightMax=%d rightSum=%lld\n", LRightMax, RRightMax, rightSum);
    if (RRightMax == LRightMax) {
      rightSum += dpRightSum[LRightMax];
    }
    MyPrintf("L = %d, R = %d, leftSum = %lld, rightSum = %lld\n", L, R, leftSum, rightSum);
    ans += leftSum * rightSum;
  }
  return ans;
}

void Solver() {  //
  scanf("%lld%lld", &c, &t);
  while (t--) {
    scanf("%lld%lld", &n, &d);
    nums.resize(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &nums[i]);
    }
    printf("%lld\n", SolverDp());
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
    output_ans = 1;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    output_ans = 0;
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  output_ans = 0;
  DiffSummary(stdout_fd);
#endif
  return 0;
}
