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
ll mapIndexs[N];      // 1-base
ll mapMergeCount[N];  // 1-base, 0 都压缩到第一个
ll mapIndexOffset = 0;
ll popcSum[N];
ll numsSum[N];

ll RangeCarry(ll l, ll r) {
  ll popc = popcSum[r] - popcSum[l - 1];
  ll num = __builtin_popcountll(numsSum[r] - numsSum[l - 1]);
  return popc - num;
}
bool CheckCarry(const ll p, const ll mid) {
  ll carry = RangeCarry(p, mid);
  return carry >= 1;
}
ll SearchFirstCarry(const ll p, const ll preFirstCarry) {
  ll l = max(preFirstCarry, p), r = min(mapIndexOffset, l + 2 * MAX_BIT + 1);
  while (l < mapIndexOffset) {
    if (CheckCarry(p, l)) {
      break;
    }
    l++;
  }
  return l;
}

bool CheckTwoCarry(const ll p, const ll mid) {
  ll carry = RangeCarry(p, mid);
  return carry >= 2;
}
ll SearchTwoCarry(const ll p, const ll preFirstTwoCarry) {
  ll l = max(preFirstTwoCarry, p), r = min(mapIndexOffset, l + 2 * MAX_BIT + 2);
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
  popcSum[0] = 0;
  numsSum[0] = 0;
  while (T--) {
    ll n = FastReadNum();
    mapIndexs[0] = -1;
    mapIndexOffset = 1;
    ll preVal = -1;
    for (int i = 1; i <= n; i++) {
      ll v = FastReadNum();
      if (v == preVal && preVal == 0) {
        mapMergeCount[mapIndexOffset - 1]++;
        continue;
      }
      mapIndexs[mapIndexOffset] = i;
      mapMergeCount[mapIndexOffset] = 1;
      popcSum[mapIndexOffset] = popcSum[mapIndexOffset - 1] + __builtin_popcountll(v);
      numsSum[mapIndexOffset] = numsSum[mapIndexOffset - 1] + v;
      preVal = v;
      mapIndexOffset++;
    }
    mapIndexs[mapIndexOffset] = n + 1;
    FenwickTree::n = mapIndexOffset;
    memset(FenwickTree::tree, 0, sizeof(FenwickTree::tree[0]) * (mapIndexOffset + 2));
    ll ans = n;
    ll firstCarry = 0;
    ll firstTwoCarry = 0;
    for (int i = 1; i < mapIndexOffset; i++) {
      firstCarry = SearchFirstCarry(i, firstCarry);  // 首个进位的下标
      if (firstCarry >= mapIndexOffset) {
        break;  // 后面的全部求和，也不会进位
      }
      firstTwoCarry = SearchTwoCarry(i, max(firstTwoCarry, firstCarry));  // 首次两次进位的下标
      //   MyPrintf("i = %d, firstCarry = %lld, firstTwoCarry = %lld\n", i, firstCarry, firstTwoCarry);
      if (firstTwoCarry == firstCarry) continue;
      ll cnt = (FenwickTree::query(i) + 1) * mapMergeCount[i] % MOD;
      ll tmpAns = (mapIndexs[firstTwoCarry] - mapIndexs[firstCarry]) * cnt % MOD;
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
