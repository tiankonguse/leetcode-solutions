/*
ID: tiankonguse
TASK: crysta
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17831
PATH: P17831 [CSP-S 2026] 能量水晶 / crystal
submission:
*/
#define TASK "crysta"
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

/*

/*

5 5
1 2 4 8 9
=> 3

5 8
-3 -1 2 2 7
=> 4
*/
ll n, m;
vector<ll> nums;

unordered_map<ll, int> firstPos;

ll SolverForce(const ll R) {  //
  ll l = R;                   // (l, R]
  ll left = m;
  MyPrintf("R = %lld, left = %lld\n", R, left);
  while (l >= 0 && left >= nums[R] - nums[l]) {
    if (nums[R] == nums[l]) {
      l--;
      continue;
    }

    // 值为 nums[l] 剩余的个数
    ll minLeft = firstPos[nums[l]];
    // 看 left 可以覆盖几个 nums[l]
    ll maxCover = left / (nums[R] - nums[l]);

    // 已经保证至少覆盖一个
    ll cover = min(maxCover, l - minLeft + 1);
    MyPrintf("l=%lld R=%lld left=%lld minLeft=%lld maxCover=%lld cover = %lld\n", l, R, minLeft, maxCover, cover);
    left -= cover * (nums[R] - nums[l]);
    l -= cover;
  }
  MyPrintf("R = %lld, l = %lld, ans = %lld\n", R, l, R - l);
  return R - l;
}

bool isProperty10_12 = false;
bool Property10_12() {  //
  for (ll v : nums) {
    if (v > 100) return false;
  }
  return true;
}

bool isPropertyA = false;
bool PropertyA() {  //
  for (int i = 0; i < n; i++) {
    if (i + 1 != nums[i]) {
      return false;
    }
  }
  return true;
}

bool CheckA(ll mid, ll R) {
  ll rightAdd = 0;
  ll leftAdd = nums[R] - nums[mid];
  ll len = R - mid + 1;
  return (rightAdd + leftAdd) * len / 2 <= m;
}
ll SolverA(ll R) {
  ll l = 0, r = R;  // [l, r]
  while (l < r) {
    ll mid = (l + r) / 2;
    if (CheckA(mid, R)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return R - r + 1;
}

bool isPropertyB = false;
bool PropertyB() {  //
  if (n == 1) return false;
  ll dis = nums[1] - nums[0];
  for (int i = 1; i < n; i++) {
    if (dis != nums[i] - nums[i - 1]) {
      return false;
    }
  }
  return true;
}

void Solver() {  //
  scanf("%lld %lld", &n, &m);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  sort(nums.begin(), nums.end());
  isProperty10_12 = Property10_12();
  isPropertyA = PropertyA();
  isPropertyB = PropertyB();
  firstPos.clear();
  for (int i = n - 1; i >= 0; i--) {
    firstPos[nums[i]] = i;
  }
  ll ans = 0;

  for (int i = 0; i < n; i++) {
    // isProperty10_12 都可以用上
    if (i + 1 < n && nums[i] == nums[i + 1]) continue;
    if (n <= 5000) {
      ans = max(ans, SolverForce(i));
    } else {
      ans = max(ans, SolverForce(i));
    }
  }
  printf("%lld\n", ans);
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
