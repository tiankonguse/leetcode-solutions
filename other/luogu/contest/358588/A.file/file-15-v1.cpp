/*
ID: tiankonguse
TASK: file
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17722?contestId=358588
PATH: P17722 [SCP-S 2026] 档案 / file
submission: https://www.luogu.com.cn/record/304516548
*/
#define TASK "file"
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

/*
思路4：第13组数据，性质A: n = 1
A 数组只有一个元素，B 序列插入到 A 前面的数字是固定的。
故，对于每个 B 序列，只关心有多少个小于 A 的数字。

假设分别有 b1、b2、...、bm 个小于 A 的数字。
如何排列 b1、b2、...、bm，才会使得代价最小呢？


不妨分析一下 b1 和 b2 的排列，看哪个代价更小。
情况1：b1 在 b2 的前面。
第一次操作：b1 个数字放在 A 前面，A 的序号是 (1+b1)，代价是 (1+b1)。
第二次操作：b2 个数字放在 A 前面，A 的序号是 (1+b1+b2)，代价是 (1+b1+b2)。
总代价是 2 + 2*b1 + b2。

情况2：b2 在 b1 的前面。
同理，代价是 2 + 2*b2 + b1。

显然，把较小的 b 放在前面，代价更小。
故可以总结出，将所有 b 按升序排列，即可使得代价最小。
*/

ll n, m;
unordered_map<ll, int> mp;
vector<ll> A;
vector<vector<ll>> B;
vector<int> vis;  // 记录当前排列
int allCnt = 0;
ll ans = 0;
vector<ll> a;
void UpdateAns() {  //
  a.clear();
  a.reserve(allCnt);
  for (int i = 0; i < n; i++) {
    a.push_back(A[i]);
  }
  ll sum = 0;
  for (int b : vis) {
    // 合并两个有序列表
    int an = a.size();
    int bn = B[b].size();
    int abn = an + bn;
    a.resize(abn);
    while (an > 0 && bn > 0) {
      if (a[an - 1] > B[b][bn - 1]) {
        a[abn - 1] = a[an - 1];
        an--;
      } else {
        a[abn - 1] = B[b][bn - 1];
        bn--;
      }
      abn--;
    }
    while (bn > 0) {
      a[abn - 1] = B[b][bn - 1];
      bn--;
      abn--;
    }
    for (int i = 1; i <= a.size(); i++) {
      if (mp.count(a[i - 1])) {
        sum += i;
      }
    }
  }
  ans = min(ans, sum);
}

void Dfs(const int leftNum) {
  if (leftNum == 0) {
    // 计算当前排列的代价
    UpdateAns();
    return;
  }
  for (int i = 0; i < leftNum; i++) {
    swap(vis[leftNum - 1], vis[i]);
    Dfs(leftNum - 1);
    swap(vis[leftNum - 1], vis[i]);
  }
}

void Solver() {  //
  scanf("%lld%lld", &n, &m);
  A.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
    mp[A[i]]++;
  }

  sort(A.begin(), A.end());

  allCnt = n;
  B.resize(m);
  vis.resize(m);
  for (int i = 0; i < m; i++) {
    vis[i] = i;
    ll L;
    scanf("%lld", &L);
    allCnt += L;
    B[i].resize(L);
    for (int j = 0; j < L; j++) {
      ll x;
      scanf("%lld", &x);
      B[i][j] = x;
    }
    sort(B[i].begin(), B[i].end());
  }

  // 暴力求 m 的排列
  ans = INT64_MAX;
  if (n == 1) {  // 性质 A
    vector<ll> b(m, 0);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < B[i].size(); j++) {
        if (B[i][j] < A[0]) {
          b[i]++;
        }
      }
    }
    sort(b.begin(), b.end());
    ans = 0;
    ll index = 1;
    for (ll v : b) {
      index += v;  // v 个数字插入到 A 前面
      ans += index;
    }
  } else {
    Dfs(m);
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
