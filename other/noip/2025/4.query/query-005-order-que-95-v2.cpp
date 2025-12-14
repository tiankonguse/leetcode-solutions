/*
ID: tiankonguse
TASK: query-A
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "query"
#define TASKEX "-005-order-que-95-v2"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

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
const int max3 = 2010, max4 = 20010, max5 = 500010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 20
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

int n, q;
ll preSums[max5];

__int128_t pow2_64 = (__int128_t(1) << 64);

ull pow2_63 = (ull(1) << 63);
inline ull Fix(ll k) {
  return ull(k);
}

pair<ll, int> que[max5];  // 单调队列, {maxVal, pos}, 递减
int qL, qR;               // [qL, qR)

deque<pair<ll, int>> queRight, queTmp;
void AddRight(deque<pair<ll, int>>& que, ll sum, int r) {
  while ((!que.empty()) && preSums[r] - sum >= preSums[que.back().second] - que.back().first) {
    que.pop_back();  // 整体单调性
  }
  que.push_back({sum, r});
}
// queLeft + queRight: preSums[second] - first 单调递减
// queRight: first 单调递增， first 相等时，preSums[second] 单调递减
ull Solver(const int L, const int R) {
  ull ans = 0;
  while (!queRight.empty()) queRight.pop_back();
  for (int r = L; r < R; r++) {
    AddRight(queRight, 0, r);
  }
  for (int i = 1; i <= n; i++) {
    if ((!queRight.empty()) && queRight.front().second == i - 1) {
      queRight.pop_front();
    }

    // 后缀长度为 r=[L,R] 的区间，原先的区间是 [i-1, r], 现在 [i,r] 也需要加进来，i 可能比 i - 1 更小
    while ((!queRight.empty()) && queRight.back().second - i + 1 >= L && queRight.back().first > preSums[i - 1]) {
      auto [sum, r] = queRight.back();
      queRight.pop_back();
      sum = preSums[i - 1];
      if ((!queTmp.empty()) && preSums[r] - sum <= preSums[queTmp.front().second] - queTmp.front().first) {
        continue;  // 从左侧插入，需要保证 区间和 左边的更大
      }
      queTmp.push_front({sum, r});
    }
    while (!queTmp.empty()) {
      auto [sum, r] = queTmp.front();
      queTmp.pop_front();
      AddRight(queRight, sum, r);
    }
    if (i + R - 1 <= n) {  // 插入长度为 R 的区间
      AddRight(queRight, preSums[i - 1], i + R - 1);
    }
    ll k = preSums[queRight.front().second] - queRight.front().first;
    ans ^= Fix(k * i);
  }
  return ans;
}

void Init() {
  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    preSums[i] += preSums[i - 1];
  }
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &preSums[i]);
  }
  Init();
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%llu\n", Solver(l, r));
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
