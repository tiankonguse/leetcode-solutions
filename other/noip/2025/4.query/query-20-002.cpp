/*
ID: tiankonguse
TASK: query
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "query"
#define TASKEX ""

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

int n, q;
ll preSums[max5];
ll sufSums[max5];
ll nums[max5];

// dpL[i] = max(sums[i,L], ..., sums[i,R])
// dpLL[i] = max(dpL[i-L+1], ..., dpL[i]);
ll dpL[max5];  // dpL[i]: 以 i 为左端点的所有极好区间的最大权值
ll dpR[max5];  // dpR[i]: 以 i 为右端点的所有极好区间的最大权值
__int128_t pow2_64 = (__int128_t(1) << 64);

ull Fix(ll k) {
  ull kk = 0;
  if (k < 0) {
    __int128_t t = k;
    t += pow2_64;
    kk = t;
  } else {
    kk = k;
  }
  return kk;
}

pair<ll, int> que[max5];  // 单调队列, {maxVal, pos}, 递减
int qL, qR;               // [qL, qR)

ull Solver(int L, int R) {
  qL = 0, qR = 0;
  for (int l = 1; l <= n; l++) {  // [l, rL) ... [l, rR)
    int r = l + L - 1;
    if (qL < qR) r = que[qR - 1].second;
    while (r <= n && r <= l + R - 1) {
      while (qL < qR && que[qR - 1].first <= preSums[r]) {
        qR--;
      }
      que[qR++] = {preSums[r], r};
      r++;
    }
    if (qL == qR) {  // 没有答案
      dpL[l] = INT64_MIN;
    } else {
      dpL[l] = que[qL].first - preSums[l - 1];
    }
    // 删除 pos = l + L - 1
    if (qL < qR && que[qL].second == l + L - 1) {
      qL++;
    }
  }

  qL = 0, qR = 0;
  for (int r = 1; r <= n; r++) {  // dpL[l] ... dpL[r]
    // pop dpL[pos] if pos + L - 1 < r
    while (qL < qR && que[qL].second + L - 1 < r) {
      qL++;
    }
    // add dpL[r]
    while (qL < qR && que[qR - 1].first <= dpL[r]) {
      qR--;
    }
    que[qR++] = {dpL[r], r};
    dpL[r] = que[qL].first;
  }

  qL = 0, qR = 0;
  for (int r = n; r >= 1; r--) {  // [lL, r] ... [lR, r]
    int l = r - L + 1;
    if (qL < qR) l = que[qR - 1].second;
    while (l >= 1 && l >= r - R + 1) {
      while (qL < qR && que[qR - 1].first <= sufSums[l]) {
        qR--;
      }
      que[qR++] = {sufSums[l], l};
      l--;
    }
    if (qL == qR) {  // 没有答案
      dpR[r] = INT64_MIN;
    } else {
      dpR[r] = que[qL].first - sufSums[r + 1];
    }
    // 删除 pos = r - L + 1
    if (qL < qR && que[qL].second == r - L + 1) {
      qL++;
    }
  }
  qL = 0, qR = 0;
  for (int l = n; l >= 1; l--) {  //  dpR[l] ... dpR[r]
    // pop dpR[pos] if pos - L + 1 > l
    while (qL < qR && que[qL].second - L + 1 > l) {
      qL++;
    }
    // add dpR[l]
    while (qL < qR && que[qR - 1].first <= dpR[l]) {
      qR--;
    }
    que[qR++] = {dpR[l], l};
    dpR[l] = que[qL].first;
  }

  ull ans = 0;
  for (int i = 1; i <= n; i++) {
    ll k = max(dpL[i], dpR[i]);
    MyPrintf("i=%d, k=%lld, dpL=%lld dpR=%lld\n", i, k, dpL[i], dpR[i]);
    ans ^= Fix(k * i);
  }

  return ans;
}
void Init() {
  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    preSums[i] = preSums[i - 1] + nums[i];
  }

  sufSums[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    sufSums[i] = sufSums[i + 1] + nums[i];
  }
}
void Solver() {  //
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &nums[i]);
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
