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

ll c, t;
ll n, d;
vector<ll> nums;

ll SolverDp() {
  ll ans = 0;
  vector<ll> dpStep, dpPath;  // dp[j] 区间 [i,j] 的最少飞行次数，以及路径数
  dpStep.resize(n);
  dpPath.resize(n);
  for (int i = 0; i < n; i++) {
    dpStep[i] = 0;
    dpPath[i] = 1;         // 自己到自己，需要0次飞行，1条路径
    int l = i, r = i + 1;  // 位置 i 为终点，距离 d 内，最小 step 的左右边界 [l, r)
    for (int j = i + 1; j < n; j++) {
      while (nums[j] - nums[l] > d) {
        l++;
      }
      if (l == j) {  // 后面的都不可到达，没答案
        break;
      }
      r = max(r, l + 1);
      while (r < j && dpStep[l] == dpStep[r]) {
        r++;
      }
      dpStep[j] = dpStep[l] + 1;
      if (r - l == 1) {
        dpPath[j] = dpPath[l];
      } else if (r - l == 2) {
        dpPath[j] = min(dpPath[l] + dpPath[l + 1], 3LL);
      } else {
        dpPath[j] = 3;  // 至少3 条路径
      }
      if (dpPath[j] == 2) {
        ans++;
      }
    }
  }
  MyPrintf("SolverDp ans = %lld\n", ans);
  return ans;
}
bool PropertyA() {
  ll dis = nums[1] - nums[0];
  for (int i = 1; i < n; i++) {
    if (dis != nums[i] - nums[i - 1]) {
      return false;
    }
  }
  return true;
}

ll SolverA() {  //
  ll dis = nums[1] - nums[0];
  if (dis * 2 > d) return 0;
  ll cnt = d / dis;
  ll minCnt = 2 * cnt;
  if (n < minCnt) return 0;
  ll ans = n - minCnt + 1;
  MyPrintf("SolverA ans = %lld\n", ans);
  return ans;
}

bool NoAns() {
  if (n <= 2) return true;
  if (nums.back() - nums.front() <= d) return true;
  return false;
}

bool PropertyB() {
  for (int i = 0; i < n; i++) {
    if (nums[i] - nums.front() <= d && nums.back() - nums[i] <= d) {
      return true;
    }
  }
  return false;
}
ll SolverB() {  //
  if (n <= 3) return 0;
  int L = n, R = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] - nums.front() <= d && nums.back() - nums[i] <= d) {
      L = min(L, i);
      R = max(R, i);
    }
  }
  if (R - L + 1 > 2) return 0;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    // 第一步，找到最大的 Ri，满足 nums[Ri -1] - nums[i] <= d
    int Ri = upper_bound(nums.begin() + i, nums.end(), nums[i] + d) - nums.begin();
    if (Ri - L > 2) break;  // 后续都没有答案
    if (Ri - i < 3) continue;
    int j = Ri - 2;
    // 第二步，找到最大的 Rj, 满足 nums[Rj] - nums[j] <= d
    int Rj = upper_bound(nums.begin() + j, nums.end(), nums[j] + d) - nums.begin();
    int k = Ri - 3;
    int Rk = upper_bound(nums.begin() + k, nums.end(), nums[k] + d) - nums.begin();
    ans += Rj - Rk;
  }
    MyPrintf("SolverB ans = %lld\n", ans);
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
    ll ans = 0;
    if (NoAns()) {
      ans = 0;
    } else if (n <= 5000) {
      ans = SolverDp();
    } else if (PropertyA()) {
      ans = SolverA();
    } else if (PropertyB()) {
      ans = SolverB();
    }
    // SolverB();

    printf("%lld\n", ans);
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
