/*
ID: tiankonguse
TASK: carry
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17729?contestId=264620
PATH: P17729 [SCP-J 2026] 进位 / carry
submission:
*/
#define TASK "carry"
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
// constexpr ll MOD = 1000000007;

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

inline ll FastReadNum() {
  char c = getchar();
  while (!(c >= '0' && c <= '9')) {  // skip blank
    c = getchar();
  }

  ll v = 0;
  while (c >= '0' && c <= '9') {
    v = v * 10 + (c - '0');
    c = getchar();
  }
  return v;
}

const ll MOD = 998244353LL;

namespace FenwickTree {

const int MAXN = 500002;
long long tree[MAXN];
int n;

int lowbit(int i) { return i & -i; }

// i 位置增加 v
void add(int i, long long v) {
  v = (v + MOD) % MOD;
  while (i <= n) {
    tree[i] = (tree[i] + v) % MOD;
    i += lowbit(i);
  }
}

// 1~i 范围的累加和
long long sum(int i) {
  long long ans = 0;
  while (i > 0) {
    ans = (ans + tree[i]) % MOD;
    i -= lowbit(i);
  }
  return ans;
}

// 原数组 [l..r] 每个数增加 v：只动差分的两端
void rangeAdd(int l, int r, long long v) {
  v = (v % MOD + MOD) % MOD;
  add(l, v);
  add(r + 1, (-v + MOD) % MOD);
}

// 原数组 i 位置的值：差分的前缀和
long long query(int i) { return sum(i); }

};  // namespace FenwickTree

const int N = 5e5 + 10;
const int MAX_BIT = 41;
ll n;
vector<ll> bitCounts[N];
bool CheckCarry(const ll p, const ll mid) {
  for (int j = 0; j < MAX_BIT; j++) {
    ll dis = bitCounts[mid][j] - bitCounts[p - 1][j];
    if (dis >= 2) {
      return true;  // 产生进位
    }
  }
  return false;
}
ll SearchFirstCarry(const ll p, const ll preFirstCarry) {
  ll l = max(preFirstCarry, p), r = n + 1;
  while (l < r) {  // [l,r)
    ll mid = (l + r) / 2;
    if (CheckCarry(p, mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

bool CheckTwoCarry(const ll p, const ll mid) {
  ll cnt = 0;
  for (int j = 0; j < MAX_BIT; j++) {
    ll dis = bitCounts[mid][j] - bitCounts[p - 1][j];
    if (dis < 2) continue;
    if (dis >= 4) {
      return true;  // 第 j 位有两次进位
    }
    if (j + 1 < MAX_BIT && bitCounts[mid][j + 1] - bitCounts[p - 1][j + 1] >= 1) {
      return true;  // 第 j 位有一次进位，第 j+1 位有一个1，会再次进位
    }
    cnt++;
    if (cnt >= 2) return true;  // 累计两次进位
  }
  return false;
}
ll SearchTwoCarry(const ll p, const ll preFirstTwoCarry) {
  ll l = max(preFirstTwoCarry, p), r = n + 1;
  while (l < r) {  // [l,r)
    ll mid = (l + r) / 2;
    if (CheckTwoCarry(p, mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l;
}
void Solver() {  //
  ll T = FastReadNum();
  bitCounts[0].resize(MAX_BIT, 0);
  while (T--) {
    n = FastReadNum();
    FenwickTree::n = n;
    memset(FenwickTree::tree, 0, sizeof(FenwickTree::tree[0]) * (n + 2));
    for (int i = 1; i <= n; i++) {
      ll v = FastReadNum();
      bitCounts[i] = bitCounts[i - 1];
      for (int j = 0; j < MAX_BIT; j++) {
        if (v & (1LL << j)) {
          bitCounts[i][j]++;
        }
      }
    }
    ll ans = n;
    ll firstCarry = 0;
    ll firstTwoCarry = 0;
    for (int i = 1; i <= n; i++) {
      firstCarry = SearchFirstCarry(i, firstCarry);  // 首个进位的下标
      if (firstCarry > n) {
        break;  // 后面的全部求和，也不会进位
      }
      firstTwoCarry = SearchTwoCarry(i, max(firstTwoCarry, firstCarry));  // 首次两次进位的下标
      //   MyPrintf("i = %d, firstCarry = %lld, firstTwoCarry = %lld\n", i, firstCarry, firstTwoCarry);
      if (firstTwoCarry == firstCarry) continue;
      ll cnt = (FenwickTree::query(i) + 1) % MOD;
      ll tmpAns = (firstTwoCarry - firstCarry) * cnt % MOD;
      //   MyPrintf("cnt = %lld tmpAns = %lld\n", cnt, tmpAns);
      ans = (ans + tmpAns) % MOD;
      FenwickTree::rangeAdd(firstCarry, firstTwoCarry - 1, cnt);
    }
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
